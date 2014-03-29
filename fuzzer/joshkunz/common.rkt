#lang racket

(provide (all-defined-out)) 

; Evaluates to #t if value 'v' is in list 'lst'. Evaluates to #f otherwise.
(define (in? v lst)
 (not (false? (member v lst))))

(define (string-empty? str)
 (string=? "" str))

(define (unreachable)
 (error 'unreachable "Reached unreachable location."))
