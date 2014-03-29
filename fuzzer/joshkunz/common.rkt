#lang racket

(require "random-extra.rkt")
(provide (all-defined-out)) 

; Evaluates to #t if value 'v' is in list 'lst'. Evaluates to #f otherwise.
(define (in? v lst)
 (not (false? (member v lst))))

(define (string-empty? str)
 (string=? "" str))

; Non-Standard specifiers (as far as I can tell) :

(define *signed-decimal*   '(d i))
(define *unsigned-decimal* '(o u x X))
(define *floating-point*   '(e E f F g G a A))
(define *character*        '(c))
(define *string*           '(s))
