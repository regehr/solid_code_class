#lang racket

(require "common.rkt")
(require "random-extra.rkt")
(require "chance.rkt")
(require "types.rkt")

(define *signed-decimal*
 (uniformly-weighted '(d i)))
(define *unsigned-decimal*
 (uniformly-weighted '(o u x X)))
(define *floating-point*
 (uniformly-weighted '(e E f F g G a A)))

(define *hash-allowed* 
 (append (no-weights *unsigned-decimal*)
         (no-weights *floating-point*)))

(define *zero-allowed*
 (append (no-weights *signed-decimal*) *hash-allowed*))

(define *field-width-range* '(-1 60))
(define *precision-range* '(-1 60))

(provide 
 type->length-specifier type->conv-specifier)

(define (type->length-specifier type)
 (match (type-size type)
  ['char 'hh]
  ['short 'h]
  ['long-int 'l]
  ['long-long-int 'll]
  ['long-double 'L]
  [_ null]
 )
)

; Evaluates to a valid printf conversion-specifier for the supplied type.
(define (type->conv-specifier type)
 (cond
  ([oftype? type *string-type*] 's)
  ([and (ofsize? 'char type) 
        (chance? 'actual-char)] 'c)
  ([oftype? type *integer-type*]
    (weighted-choice 
     (if (signed? type) *signed-decimal* *unsigned-decimal*)))
  ([oftype? type *float-type*]
   (weighted-choice *floating-point*))
 )
)

(provide 
 fmt fmt? fmt-flags fmt-width fmt-precision fmt-length fmt-conversion
 fmt-flags->string fmt-width->string fmt-precision->string fmt-length->string
 fmt-conversion->string)

(struct fmt 
 (flags width precision length conversion) #:transparent)

(define (fmt-flags->string fmt)
 (if [null? (fmt-flags fmt)] ""
  (fmt-flags fmt)))

(define (fmt-width->string fmt) 
 (if [null? (fmt-width fmt)] ""
  (format "~a" (fmt-width fmt))))

(define (fmt-precision->string fmt)
 (match (fmt-precision fmt)
  [null   ""]
  ['empty "."]
  [_ (format ".~a" (fmt-precision fmt))]
 )
)

(define (fmt-length->string fmt)
 (if [null? (fmt-length fmt)] ""
  (symbol->string (fmt-length fmt))))

(define (fmt-conversion->string fmt)
 (symbol->string (fmt-conversion fmt)))

; **** Generation ****

(provide gen-fmt)

(define (gen-flags type conv)
 (string-append
  (if [and (in? conv *hash-allowed*)
           (chance? 'hash-flag)] "#" "")
  (if [and (in? conv *zero-allowed*)
           (chance? 'zero-flag)] "0" "")
  (if [chance? 'left-flag] "-" "")
  (if [and (signed? type)
           (chance? 'space-flag)] " " "")
  (if [and (signed? type)
           (chance? 'sign-flag)] "+" "")
 )
)

(define (gen-width)
 (apply random-integer *field-width-range*))

(define (gen-precision)
 (if (chance? 'precision-dotonly) 'empty
  (apply random-integer *precision-range*)))

(define (gen-fmt type)
 (let ([conv (type->conv-specifier type)])
  (fmt
   (if (chance? 'format-flags) 
    (gen-flags type conv) null)
   (if (chance? 'format-width)
    (gen-width) null)
   ; Precision is not valid for character conversions
   (if [and (not (eq? conv 'c)) 
            (chance? 'format-precision)]
    (gen-precision) null)
   ; Chars have a length specifier, but if we want print a char
   ; as an actual character we shouldn't include it.
   (if (not (eq? 'c conv))
    (type->length-specifier type) null)
   conv
  )
 )
)
