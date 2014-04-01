#lang racket

(require "random-extra.rkt")

(provide chance chance?)

(define *chances* '(
 ; Probability that we'll generate a 'nan' or 'inf',
 ; value for a floating-point argument
 (gen-nan 0.1)
 (gen-inf 0.1)

 ; Probablility that a 'char' type will get an actual 'c' conversion specifier
 ; instead of an 'hh' length modifier.
 (actual-char 0.5)

 ; Probability that some format fields will be converted to arguments.
 (star-args 0.3)

 ; Probabilities on whether or not to include certain parts of
 ; a format specifier
 (format-flags 0.3)
 (format-width 0.3)
 (format-precision 0.3)
 ;(format-flags 0.0)
 ;(format-width 0.0)
 ;(format-precision 0.0)

 ; The probability that we'll generate precision field
 ; that consists of a single '.'.
 (precision-dotonly 0.1)

 ; Probability that an unsigned integer argument will be cast as a pointer.
 (pointer-conversion 0.3)

 ; Various flag probabilities
 (hash-flag  0.3)
 ;(hash-flag  0.0)
 (zero-flag  0.3)
 ;(zero-flag  0.0)
 (left-flag  0.3)
 (space-flag 0.3)
 (sign-flag  0.3)
))

; Get the chance for a given symbol
(define (chance sym)
 (cadr (assoc sym *chances*)))

(define (chance? sym)
 (< (random-real 0 1) (chance sym)))
