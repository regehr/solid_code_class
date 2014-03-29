#!/usr/bin/env racket
#lang racket

(require racket/date)
(require "printf.rkt" "output.rkt")

(define fuzz-src-name "fuzz.c")
(define printf-max 1000)

(define gcc (find-executable-path "gcc"))
(define coverage-flags '("-fprofile-arcs" "-ftest-coverage"))

(define diff-count 0)
(define printf-count 0)

(define (compile out objs [args '()])
  (if (apply system* `(,gcc ,@args ,"-o" ,out ,@objs))
    #t
    (raise-user-error 'compile "Couldn't compile to ~a.~%" out)))

(define (compile-o src-name [args '()])
  (if (apply system* `(,gcc ,@args ,"-c" ,src-name))
    #t
    (raise-user-error 'compile-o "Couldn't compile .o from ~a.~%" src-name)))

(define (date-print str . rest)
  (let* ([now (current-date)])
    (printf "[~a/~a - ~a:~a:~a]: " (date-month now) (date-day now) (date-hour now) (date-minute now) (date-second now))
    (printf str rest)
    (printf "~%")))

(define (go)
  (define printfs
    (let ([n-printf (+ 1 (random printf-max))])
      (build-list n-printf (lambda (n) (generate-printf)))))

  (date-print "New iteration... (~a printf's executed)" printf-count)

  (set! printf-count (+ printf-count (length printfs)))

  ; Create source file
  (printfs-to-file printfs fuzz-src-name)

  ; Compile files
  (compile-o fuzz-src-name)
  (compile "fuzz"
           '("fuzz.o" "fwrite.o" "snprintf.o" "vfprintf-fixed.o" "vsnprintf.o")
           coverage-flags)
  (system* "fuzz")

  ; Run the diff
  (if (= (system*/exit-code (find-executable-path "diff") "-a" "musl.bin" "glibc.bin") 0)
    #t
    (begin ; Save source that triggers differences
      (set! diff-count (+ diff-count 1))
      (let ([err-src-name (string-append "diff" (number->string diff-count) ".c")])
        (printf "Difference found: offending source moved to ~a.~%" err-src-name)
        (printfs-to-file printfs err-src-name #f)
        (rename-file-or-directory fuzz-src-name (string-append err-src-name "-orig.c") #t))))

    (go))

(void
  (compile-o "../musl-printf-standalone/fwrite.c")
  (compile-o "../musl-printf-standalone/snprintf.c")
  (compile-o "vfprintf-fixed.c" coverage-flags)
  (compile-o "../musl-printf-standalone/vsnprintf.c"))

(go)
