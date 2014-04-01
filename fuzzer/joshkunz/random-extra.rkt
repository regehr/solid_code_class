#lang racket

(provide
 random-real
 random-integer
 random-bytes
 pick
 vector-pick)

; **** General ****

; Generate a random real number in the range [a, b].
(define (random-real a b)
 (+ (* (random) 
     (- (max a b) (min a b)))
  (min a b)))

; Generate a random integer in the range [a b].
(define (random-integer a b)
 (exact-truncate (random-real a b)))

(define (random-bytes byte-count)
 (if (= byte-count 0) #""
  (bytes-append 
   (bytes (random-integer 0 255)) 
   (random-bytes 
    (sub1 byte-count)))))

; Pick a random entry from the given (uniformly-distributed) list
(define (pick lst)
 (list-ref lst (random-integer 0 (sub1 (length lst)))))

; Pick a random entry in the given (uniformly-distributed) vector
(define (vector-pick vec)
 (vector-ref vec (random-integer 0 (sub1 (vector-length vec)))))

; **** Weights ****

(provide
 weights
 no-weights
 uniformly-weighted
 weighted-choice)

(define (weights lst)
 (map car lst))

(define (no-weights lst)
 (map cadr lst))

(define (uniformly-weighted lst)
 (let ([prob (/ 1 (length lst))])
  (map (lambda (item) (list prob item)) lst)
 )
)

; Find the appropriate choice given a weighted list and a correctly-generated
; random number. Usually called by weighted-choice.
(define (find-weighted-choice lst rand)
 (let* ([weight (caar lst)]
        [nrand (- rand weight)])
  (if (<= nrand 0) (cadar lst) (find-weighted-choice (cdr lst) nrand))))

; Assuming that lst is a list of pairs in the form (weight value),
; return a randomly chosen (distributed according to the given weights)
; 'value' from a pair.
(define (weighted-choice lst)
 (let ([wsum (apply + (weights lst))])
  (find-weighted-choice lst (random-real 0 wsum))
 )
)
