#lang racket

(require (only-in racket/generator generator yield)
         (only-in rnrs/base-6 assert))

(require "term-colors.rkt")
(require "framework.rkt")

; The exit code proper huff implementations are supposed to fail with.
(define *failure* 255)
(define *success* 0)

; HURL file magic number
(define *huff-magic* (string->bytes/utf-8 "HUFF"))

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
 (if (= (length table) 256) table
  ; Generate the next table entry.
  (valid-tree (cons 
              (string-append (make-string (length table) #\0) "1") table))
 )
)

; Return the byte representation of the supplied table.
(define (table->bytes table)
 (string->bytes/utf-8 
  (string-join table "\n" #:after-last "\n"))
)

; ***** CHECKERS ***** ;

(define (expect-code expected-code)
 (lambda (code stdout stderr)
  (if (not (= code expected-code))
   (list #f
    (format "Bad error code: ~a (expected ~a)" code expected-code))
   (list #t))
 )
)

; Prints out stderr, always succeeds
(define (print-output code stdout stderr)
 (list #t 
  (string-append (style "stdout" (make-color 'white)) "\n"
   (string-trim (bytes->string/utf-8 stdout)))
  (string-append (style "stderr" (make-color 'white)) "\n"
   (string-trim (bytes->string/utf-8 stderr)))
 )
)

; ***** TESTS ******* ;

(define (no-magic)
 (generator ()
  (yield (length-as-bytes 1))
  (yield (table->bytes (valid-tree)))
  (yield (hex-string->bytes "80"))
  (yield 'stop)
 )
)

(define (bad-table-entry)
 (generator ()
  (yield *huff-magic*)
  (yield (length-as-bytes 1))
  (yield (table->bytes
          (append (cdr (valid-tree)) '("2"))))
  (yield (hex-string->bytes "80"))
  (yield 'stop)
 )
)

(define (empty-huff)
 (generator ()
  (yield *huff-magic*)
  (yield (length-as-bytes 0))
  (yield (table->bytes (valid-tree)))
  (yield 'stop)
 )
)

(define (normal-huff)
 (generator ()
  (yield *huff-magic*)
  (yield (length-as-bytes 1))
  (yield (table->bytes (valid-tree)))
  (yield (hex-string->bytes "80"))
  (yield 'stop)
 )
)

(define (bad-length)
 (generator ()
  (yield *huff-magic*)
  (yield (length-as-bytes 1))
  (yield (table->bytes (valid-tree)))
  (yield 'stop)
 )
)

(define (test-all . tests)
 (unless (null? tests)
  (apply test (car tests))
  (apply test-all (cdr tests))
 )
)

(define (huff-decompress name file-generator expected-code 
         #:file-base [file-base "t"] . checkers)
 (let ([huff-name (string-append file-base ".huff")])
  (test name
   (list (build-file file-generator huff-name))
   (run-binary "huff" "-d" huff-name)
   (append (list (expect-code expected-code)) checkers)
   #:finally (list (rm file-base)))
 )
)

(begin0 (void)
(huff-decompress "Simple decompression"
 (normal-huff) *success* print-output)
(huff-decompress "Empty huff file" 
 (empty-huff) *success* print-output)
(huff-decompress "Incorrect length in huff file"
 (bad-length) *failure* print-output)
(huff-decompress "No magic number in huff file"
 (no-magic) *failure* print-output)
(huff-decompress "2 in translation table"
 (bad-table-entry) *failure* print-output)
(test "Wrong extension"
 (list (build-file (normal-huff) "t"))
 (run-binary "huff" "-d" "t")
 (list (expect-code *failure*) print-output))
)

