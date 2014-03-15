#lang racket

(require (only-in rnrs/base-6 assert))
(require "term-colors.rkt")
(require "framework.rkt")

; The exit code proper huff implementations are supposed to fail with.
(define *failure* 255)
(define *success* 0)

(define *huff-magic* (string->bytes/utf-8 "HURL"))
(define *huff-ext* ".hurl")
(define *huff-bin* "rhuff")

(define (test-success stdout stderr) (list #t))

; Convert a string containing hexadecimal characters into a bytestring
(define (hex-string->bytes string)
 (hex-chars->bytes (string->list string)))

; Convert a list of hex characters into a bytestring
; (helper for hex-string->bytes)
(define (hex-chars->bytes chars [bytes '()])
 (cond
  [(null? chars) (list->bytes bytes)]
  [(= (length chars) 1) (error "Could not translate odd-length string.")]
  [else
   (let*-values ([(head tail) (split-at chars 2)]
                [(value) (string->number (list->string head) 16)])
    (assert (byte? value))
    (hex-chars->bytes tail (cons value bytes))
   )]
 )
)

; Return the number 'length' as an unsigned long long
(define (length-as-bytes length) 
 (integer->integer-bytes length 8 #f))

; Generate a valid, yet non-sensical tree.
(define (valid-tree [table '("1")])
 (if (= (length table) 255) (cons (make-string 255 #\0) table)
  ; Generate the next table entry.
  (valid-tree (cons 
              (string-append (make-string (length table) #\0) "1") table))
 )
)

(define (character->bit char)
 (assert (or (char=? char #\1) (char=? char #\0)))
 (if (char=? char #\1) 1 0)
)

(define (character-list->byte char-bits [byte 0] [index 7])
 (if (null? char-bits) byte
  (character-list->byte 
   (cdr char-bits)
   (bitwise-ior byte
    (arithmetic-shift (character->bit (car char-bits)) index))
   (sub1 index)
  )
 )
)

(define (_list-entry->bytes entry [lbytes '()])
 (assert (= (modulo (length entry) 8) 0))
 (if (null? entry) (apply bytes (reverse lbytes))
  (let*-values ([(bit-list rest) (split-at entry 8)])
   (_list-entry->bytes rest (cons (character-list->byte bit-list) lbytes))
  )
 )
)


(define (string-entry->bytes entry)
 (let* ([length-modulo (modulo (string-length entry) 8)]
        [compensation
         (if (not (= length-modulo 0))
          (make-string (- 8 length-modulo) #\0) "")])
  (_list-entry->bytes (string->list (string-append entry compensation)))
 )
)

; Should return the bytes that make up the huff table entry
; that translates to an 8 length run of a 1 bit.
(define (valid-rle-entry table)
 (string-entry->bytes 
  (list-ref table (string->number "#x88")))
)

; Return the byte representation of the supplied table.
(define (table->bytes table)
 (string->bytes/utf-8 
  (string-join table "\n" #:after-last "\n"))
)

; ***** CHECKERS ***** ;

(define (file-exists filename) (thunk*
 (if (file-exists? filename) (list #t)
  (list #f (format "Expected file '~a' to exist, but it wasn't found." filename))
 )
))

;(define (files-match? A B #:hexdiff [hexdiff? #t])
; (if
;  (let ([port_a (open-input-file A #:mode 'binary)]
;        [port_b (open-input-file B #:mode 'binary)])
;   (begin0 
;    (and
;     (for ([ab port_a] [bb port_b] #:finally (not (= ab bb)))
;      (= ab bb))
;     (= (sequence-length port_a) (sequence-length port_b))
;    )
;    (close-input-port port_a)
;    (close-input-port port_b)
;   )
;  )
; ) #t
; (when hexdiff?)
;  (
;)

(define (expect-code expected-code)
 (lambda (results)
  (let ([exit-code (car (hash-ref results 'status))])
   (if (not (= exit-code expected-code))
    (list #f
     (format "Bad error code: ~a (expected ~a)" exit-code expected-code))
    (list #t))
   )
 )
)

; Prints out stderr, always succeeds
(define (print-info results)
 (let* ([heading-color (make-color 'white)]
        [heading (lambda (text) (style text heading-color))]
        [result (lambda (key) (car (hash-ref results key)))])
  (list #t 
   (string-append (heading "invocation: ") 
    (string-join (cons (result 'binary) (result 'args)) " "))
   (string-append (heading "stdout:") "\n"
    (string-trim (bytes->string/utf-8 (result 'stdout))))
   (string-append (heading "stderr:") "\n"
    (string-trim (bytes->string/utf-8 (result 'stderr))))
  )
 )
)

; ***** TESTS ******* ;

(define (normal-huff)
 (let ([table (valid-tree)])
  (list
   *huff-magic*
   (length-as-bytes 1)
   (table->bytes table)
   (valid-rle-entry table)
  )
 )
)

(define (no-magic)
 (let ([table (valid-tree)])
  (list
   (length-as-bytes 1)
   (table->bytes table)
   (valid-rle-entry table)
  )
 )
)

(define (bad-table-entry)
 (let ([table (append (cdr (valid-tree)) '("2"))])
  (list
   *huff-magic*
   (length-as-bytes 1)
   (table->bytes table)
   (valid-rle-entry table)
  )
 )
)

(define (empty-huff)
 (list
  *huff-magic*
  (length-as-bytes 0)
  (table->bytes (valid-tree))
 )
)

(define (bad-rle)
 (let ([table (valid-tree)])
  (list
   *huff-magic*
   (length-as-bytes 1)
   (table->bytes table)
   ; Translates to RLE code encoding for a run of 7 1s
   (string-entry->bytes 
    (list-ref table (string->number "#x87")))
  )
 )
)

(define (no-byte-translation)
 (let ([table (valid-tree)])
  (list
   *huff-magic*
   (length-as-bytes 1)
   (table->bytes table)
   (hex-string->bytes "00")
  )
 )
)

(define (bad-length)
 (list
  *huff-magic*
  (length-as-bytes 1)
  (table->bytes (valid-tree))
 )
)

(define (huff-decompress name file-bytes expected-code 
         #:file-base [file-base "t"] . checkers)
 (let ([huff-name (string-append file-base *huff-ext*)]
       [extra-checkers (if (= expected-code *success*)
                        (cons (file-exists file-base) checkers) checkers)])
  (test name
   (list (build-file (in-list file-bytes) huff-name))
   (run-binary *huff-bin* "-d" huff-name)
   (append (list (expect-code expected-code)) extra-checkers)
   #:finally (list (rm file-base)))
 )
)


;(define (huff-cycle name file-sequence file-base . checkers)
; (let ([huff-name (string-append file-base *huff-hext*)])
;  (test (string-append name ": Compress")
;   (list (build-file file-sequence file-base) 
;         (cp file-base (string-append file-base ".bak")))
;   (run-binary *huff-bin* "-c" file-base)
;   (append (list (expect-code *success*) (file-exists huff-name)) checkers)
;  )
;  (test (string-append name ": Decompress")
;   (list)
;   (run-binary *huff-bin* "-d" huff-name)
;   (append (list (expect-code *success*) (file-exists huff-name)) checkers)
;  )
; )
;)


(begin0 (void)
(huff-decompress "Simple decompression"
 (normal-huff) *success* print-info)
(huff-decompress "Empty huff file" 
 (empty-huff) *success* print-info)
(huff-decompress "Incorrect length in huff file"
 (bad-length) *failure* print-info)
(huff-decompress "Decompress compressed file where bytes not in translation table"
 (no-byte-translation) *failure* print-info)
(huff-decompress "No magic number in huff file"
 (no-magic) *failure* print-info)
(huff-decompress "2 in translation table"
 (bad-table-entry) *failure* print-info)
(test "Wrong extension"
 (list (build-file (normal-huff) "t.huff"))
 (run-binary *huff-bin* "-d" "t")
 (list (expect-code *failure*) print-info))
(huff-decompress "RLE encodes number of bits not divisible by 8"
 (bad-rle) *failure* print-info)
)

