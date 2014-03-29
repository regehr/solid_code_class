#lang racket

(require "common.rkt")
(require "random-extra.rkt")

(provide
 *integer-type* *float-type* *string-type*)

(define *integer-type* '(char short int long-int long-long-int))
(define *float-type*   '(float double long-double))
(define *string-type*  '(char*))

(define *type-sizes* 
 (uniformly-weighted 
  (append *integer-type* *float-type* *string-type*)))

(define *type-signs*
 (uniformly-weighted '(signed unsigned)))

(define *string-length-range* '(5 50))

; Evaluates a list of characters in the range [start, end]
(define (char-range start end)
 (map integer->char (range start (add1 end))))

; Vector of non-whitespace (except SPACE) characters not including
; ('), (") and (\).
(define *valid-characters* (list->vector
 (append (char-range 32 33) 
         (char-range 35 38) 
         (char-range 40 91)
         (char-range 93 126))))

; 32-bit numeric-type bit-depths
(define *bit-widths* '(
 (char 8)
 (short 16)
 (int 32)
 (long-int 32)
 (long-long-int 64)
 (float 32)
 (double 64)
 (long-double 96)
))

; Interface 
(provide
 type type? type-size ofsize? signed? oftype? type-gen 
 type-value type-bit-width type-postfix
 type-size->string type-value->string type->string)

(struct type (signed? size gen writer) #:transparent)

(define (signed? type) 
 (type-signed? type))

(define (ofsize? size type)
 (eq? size (type-size type)))

(define (oftype? type class)
 (in? (type-size type) class))

(define (type-bit-width type)
 (cadr (assoc (type-size type) *bit-widths*))) 

(define (type-postfix type)
 (string-append 
  (if (signed? type) "" "U")
  (match (type-size type)
   ['long-int      "L"]
   ['long-long-int "LL"]
   ['float         "F"]
   ['long-double   "L"]
   [_ ""]
  )
 )
)

(define (type-size->string type)
 (string-replace (symbol->string (type-size type)) "-" " "))

(define (type-value type)
 ((type-gen type) type))

(define (type-value->string type)
 ((type-writer type) type))

(define (type->string type)
 (string-append
  (if (signed? type) "" "unsigned ")
  (type-size->string type)
  " = "
  (type-value->string type)
 )
)

; **** Value Writers ****

(define (integer-writer type)
 (string-append
  (format "~a" (type-value type))
  (type-postfix type)))

(define (float-writer type)
 (let ([value (type-value type)]
       [size (type-size type)])
  (cond 
   ([nan? value]
    (string-append "(" (type-size->string type) ") "
     (if (or (eqv? +nan.0 value)
             (eqv? +nan.f value)) "NAN" "-NAN")))
   ([infinite? value]
    (string-append "(" (type-size->string type) ") "
     (if (or (eqv? +inf.0 value)
             (eqv? +inf.f value)) "INFINITY" "-INFINITY")))
   (else
    (string-append (format "~a" value) (type-postfix type))
   )
  )
 )
)

(define (string-writer type)
 (string-append "\"" (apply string (type-value type)) "\""))

; Generation

(provide gen-type)

(define (gen-string type)
 (define (_gen-string len)
  (if (= len 0) '()
   (cons (vector-pick *valid-characters*) (_gen-string (sub1 len))))
 )
 (_gen-string (apply random-integer *string-length-range*)))

; Generate a random real floating-point number.
(define (gen-float type)
 (let ([bytes (/ (type-bit-width type) 8)])
  (floating-point-bytes->real
   (if (< bytes 8) (random-bytes 4) (random-bytes 8))
  )
 )
)

(define (gen-integer type)
 (let ([bit-width (type-bit-width type)])
  (if (signed? type)
   ; For signed
   (random-integer
    (* -1 (expt 2 (- bit-width 1))) ; -2^(w -1)
    (- (expt 2 (- bit-width 1)) 1)  ; 2^(w-1) - 1
   )
   ; For unsigned 
   (random-integer 0 (- (expt 2 bit-width) 1)) ; 2^w - 1
  )
 )
)

(define (gen-type)
 (let ([sign (weighted-choice *type-signs*)]
       [size (weighted-choice *type-sizes*)])
  ; Float types can't be unsigned, so make sure we only set the sign-value
  ; for integer types.
  (cond
   ([in? size *float-type*] 
    (type #t size gen-float float-writer))
   ([in? size *string-type*]
    (type #f size gen-string string-writer))
   ([in? size *integer-type*]
    (type sign size gen-integer integer-writer))
  )
 )
)
