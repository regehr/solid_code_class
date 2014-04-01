#lang racket

(provide (all-defined-out)) 

; Evaluates to #t if value 'v' is in list 'lst'. Evaluates to #f otherwise.
(define (in? v lst)
 (not (false? (member v lst))))

(define (string-empty? str)
 (string=? "" str))

; Post-increment assignment macro.
(define-syntax-rule (set++! value)
 (begin value (set! value (add1 value))))

; Like 'assf', but instead of returning the found element,
; it returns the position of the element in the list.
(define (assf-index proc v lst [index 0])
 (cond
  ([null? lst] #f)
  ([and (pair? (car lst)) 
        (proc v (caar lst))] index)
  (else (assf-index proc v (cdr lst) (add1 index)))))

; Evaluates to a new list of pairs, where the right hand side of
; each pair in the new list, was it's index+1 in the given list.
(define (enumerate lst [depth 1])
 (if (null? lst) '()
  (cons
   (list depth (car lst))
   (enumerate (cdr lst) (add1 depth)))))

(define (byte->hex-string byte)
 (let ([hex (number->string byte 16)])
  (if (< (string-length hex) 2)
   (string-append "0" hex)
   hex)))

(define (bytes->hex-string bytes)
 (string-join (map byte->hex-string (bytes->list bytes)) ""))

(define (unreachable)
 (error 'unreachable "Reached unreachable location."))
