#lang racket

(require (only-in racket/generator generator yield)
         (only-in rnrs/base-6 assert))

; The exit code proper huff implementations are supposed to fail with.
(define *failure-code* 255)
(define *success-code* 0)

(define *SUCCS* #f)
(define *FAILS* #t)

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
  [(= (length chars) 0) (list->bytes bytes)]
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
  (string-join (valid-tree) "\n" #:after-last "\n"))
)

; Write the supplied test-generator to the given port by generating
; test outputs.
(define (write-test test-generator to-file)
 (let ([writer (lambda (bytes) 
               (write-bytes bytes to-file))])
  (map writer (sequence->list 
               (in-producer test-generator 'stop)))
 )
)


; Run a test that builds a test-file using 'test-generator', passes test-file
; to the test program, and then checks for the proper error code.
(define (run-test test-generator flag 
                  #:bin [bin "huff"] 
                  #:temp-file [temp-file "test.huff"]
                  #:echo [echo? #t])
 ; Write out our test file.
 (let ([out-file (open-output-file temp-file #:exists 'truncate)])
  (write-test test-generator out-file)
  (close-output-port out-file)
 )
 (when echo? (printf "$ ~a ~a ~a\n" bin flag temp-file))
 ; Run the program as a subprocess 
 (let-values ([(proc proc-stdout proc-stdin proc-stderr)
               (subprocess #f #f #f bin flag temp-file)])
  (begin0
   ; Collect the process's output and status code for return
   (let ([proc-output (port->bytes proc-stdout)]
         [proc-error (port->bytes proc-stderr)])
    (subprocess-wait proc)
    (list (subprocess-status proc) proc-output proc-error)
   )
   ; Cleanup the communication channels.
   (close-output-port proc-stdin)
   (close-input-port proc-stdout)
   (close-input-port proc-stderr)
  )
 )
)

; General test result checking code. Evaluates to #t if the test passed,
; and evaluates to #f if the test failed.
(define (check-test test-name test-output fail? . test-checks)
 (let-values ([(code stdout stderr) (apply values test-output)])
  (let* ([expected-code (if fail? *failure-code* *success-code*)]
         [correct-status? (= code expected-code)]
         [check-runner (lambda (check) (check stdout stderr))]
         [check-results (map check-runner test-checks)]
         [checks-passed? (andmap car check-results)])
   (if (and correct-status? checks-passed?)
    (begin0 #t
     (printf "Test '~a' passed.\n" test-name))
    (begin0 #f ; else
     (printf "Test '~a' failed.\n" test-name)
     (printf "    Error code: ~a (expected ~a)\n" code expected-code)
     (let ([make-lines (lambda (outputs)
                        (string-join 
                         (map (lambda (v) (string-append "    " v)) outputs)
                         "\n"))])
      (display (string-join 
                (map (lambda (v) (make-lines (cdr v))) check-results) 
                "\n" #:after-last "\n"))
     )
    )
   )
  )
 )
)

; Runs all supplied tests. 
(define (test-all . tests)
 (let*-values ([(environment predicates) (split-at (car tests) 5)]
               [(test-name generator flag file-name succeeds) 
                (apply values environment)])
  (if (apply check-test (append (list test-name
       (run-test generator flag #:temp-file file-name) succeeds) predicates))
   (delete-file file-name)
   (let ([saved-file-name 
          (string-append (string-downcase
           (string-replace (string-normalize-spaces test-name) " " "-"))
           ".input")])
    (rename-file-or-directory file-name saved-file-name #t)
    (printf "Triggering input saved into: ~a\n" saved-file-name)
   )
  )
 )
 (unless (= (length tests) 1) 
  (apply test-all (cdr tests)))
)

; ***** CHECKERS ***** ;

; Prints out stderr, always succeeds
(define (output-printer stdout stderr)
 (list #t 
   (string-append "Stdout: " (bytes->string/utf-8 stdout))
   (string-append "Stderr: " (bytes->string/utf-8 stderr))
 )
)

; ***** TESTS ******* ;

(define empty-huff
 (generator ()
  (yield *huff-magic*)
  (yield (length-as-bytes 0))
  (yield (table->bytes (valid-tree)))
  (yield 'stop)
 )
)

(define bad-length
 (generator ()
  (yield *huff-magic*)
  (yield (length-as-bytes 1))
  (yield (table->bytes (valid-tree)))
  (yield 'stop)
 )
)

(display (current-namespace)) (newline)
(display (namespace-mapped-symbols)) (newline)

(display "Running tests...\n")
(test-all
 (list "Empty huff file" 
  empty-huff "-d" "t.huff" *FAILS* output-printer)
 (list "Incorrect huff file length" 
  bad-length "-d" "t.huff" *FAILS* output-printer)
)
