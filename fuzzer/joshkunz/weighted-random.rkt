#lang racket

(provide
 uniformly-weighted
 random-between
 random-int-between
 weighted-choice
 weights
 no-weights)

(define (uniformly-weighted lst)
 (let ([prob (/ 1 (length lst))])
  (map (lambda (item) (list prob item)) lst)
 )
)

; Generate a number between a b, may not be an integer.
(define (random-between a b)
 (+ (* (random) 
     (- (max a b) (min a b)))
  (min a b))
)

; The same as random-between except only generates integers.
(define (random-int-between a b)
 (exact-truncate (random-between a b))
)

(define (weights lst)
 (map car lst))

(define (no-weights lst)
 (map cadr lst))

; Find the appropriate choice given a weighted list and a correctly-generated
; random number. Usually called by weighted-choice.
(define (find-weighted-choice lst rand)
 (let* ([weight (caar lst)]
        [nrand (- rand weight)])
  (if (<= nrand 0) (cadar lst)
   (find-weighted-choice (cdr lst) nrand))
 )
)

; Assuming that lst is a list of pairs in the form (weight value),
; return a randomly chosen (distributed according to the given weights)
; 'value' from a pair.
(define (weighted-choice lst)
 (let ([wsum (apply + (weights lst))])
  (find-weighted-choice lst (random-between 0 wsum))
 )
)
