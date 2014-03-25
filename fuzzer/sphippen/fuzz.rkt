#!/usr/bin/env racket
#lang racket

(require "printf.rkt" "output.rkt")

(define src-name "fuzz.c")
(define printf-max 10)

(define diff-count 0)

(define (compile cc out)
  (if (system* cc "-o" out src-name)
    #t
    (raise-user-error 'compile "Couldn't compile to ~a using ~a.~%" out cc)))

(define go
  (define printfs
    (let ([n-printf (random printf-max)])
      (build-list n-printf (lambda (n) (gen-printf)))))

  ; Create source file
  (printfs-to-file printfs src-name)

  ; Compile files
  (compile "/home/sphippen/libs/musl/bin/musl-gcc" "musl-fuzz")
  (rename-file-or-directory "out.bin" "musl.bin" #t)
  (compile "gcc" "glibc-fuzz")
  (rename-file-or-directory "out.bin" "glibc.bin" #t)

  ; Run the diff
  (if (= (system*/exit-code "diff" "-a" "musl.bin" "glibc.bin") 0)
    #t
    (begin ; Save source that triggers differences
      (set! diff-count (+ diff-count 1))
      (let ([src-name (string-append "diff" (number->string diff-count) ".c")])
        (display "Difference found: offending source moved to ~a.~%" src-name)
        (rename-file-or-directory src-name src-name #t))))

    (go))

(go)
