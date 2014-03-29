#!/usr/bin/env racket
#lang racket

(require racket/date)
(require "compare.rkt" "printf.rkt")

(define printf-max 1000)

(define diff-count 0)
(define printf-count 0)

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

  (if (test-printfs printfs diff-count)
    (void)
    (set! diff-count (+ diff-count 1)))

  (go))

(setup)
(go)
