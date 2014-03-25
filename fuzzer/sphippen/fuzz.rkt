#!/usr/bin/env racket
#lang racket

(require racket/date)
(require "printf.rkt" "output.rkt")

(define src-name "fuzz.c")
(define printf-max 1000)

(define diff-count 0)

(define (compile cc out . args)
  (if (apply system* `(,cc ,@args ,"-o" ,out ,src-name))
    #t
    (raise-user-error 'compile "Couldn't compile to ~a using ~a.~%" out cc)))

(define (date-print str)
  (let* ([now (current-date)])
    (printf "[~a/~a - ~a:~a:~a]: ~a~%" (date-month now) (date-day now) (date-hour now) (date-minute now) (date-second now) str)))

(define (go)
  (define printfs
    (let ([n-printf (random printf-max)])
      (build-list n-printf (lambda (n) (gen-printf)))))

  (date-print "New iteration...")

  ; Create source file
  (printfs-to-file printfs src-name)

  ; Compile files
  (compile "/home/sphippen/libs/musl/bin/musl-gcc" "musl-fuzz" "-static")
  (compile (find-executable-path "gcc") "glibc-fuzz")

  (system* "musl-fuzz")
  (rename-file-or-directory "out.bin" "musl.bin" #t)
  (system* "glibc-fuzz")
  (rename-file-or-directory "out.bin" "glibc.bin" #t)

  ; Run the diff
  (if (= (system*/exit-code (find-executable-path "diff") "-a" "musl.bin" "glibc.bin") 0)
    #t
    (begin ; Save source that triggers differences
      (set! diff-count (+ diff-count 1))
      (let ([err-src-name (string-append "diff" (number->string diff-count) ".c")])
        (printf "Difference found: offending source moved to ~a.~%" err-src-name)
        (rename-file-or-directory src-name err-src-name #t))))

    (go))

(go)
