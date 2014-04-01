#lang racket

(require "common.rkt")
(require "random-extra.rkt")
(require "chance.rkt")
(require "types.rkt")

(define *signed-decimal*
 (uniformly-weighted '(d i n)))

(define *unsigned-decimal*
 (uniformly-weighted '(o u x X)))
;(define *unsigned-decimal*
; (uniformly-weighted '(u x X)))

(define *floating-point*
 (uniformly-weighted '(e E f F g G a A)))
;(define *floating-point*
; (uniformly-weighted '(e E f F g G)))

(define *string*
 (uniformly-weighted '(s m)))
; Specified below: c p

(define *hash-allowed* 
 (append '(p) (remove 'u (no-weights *unsigned-decimal*))
              (no-weights *floating-point*)))

(define *zero-allowed*
 (append (no-weights *signed-decimal*) *hash-allowed*))

; These format specifiers can never have anything more then length modifiers
(define *length-only* '(m n p))

(define *field-width-range* '(-5 275))
(define *precision-range* '(0 60))

(provide 
 type->length-specifier type->conv-specifier)

(define (type->length-specifier type)
 (match (type-size type)
  ['char 'hh]
  ['short 'h]
  ['wint_t 'l]
  ['wchar_t* 'l]
  ['long-int 'l]
  ['long-long-int 'll]
  ['long-double 'L]
  ['intmax_t 'j]
  ['uintmax_t 'j]
  ['size_t 'z]
  ['ssize_t 'z]
  ['ptrdiff_t 't]
  [_ null]
 )
)

; Evaluates to a valid printf conversion-specifier for the supplied type.
(define (type->conv-specifier type)
 (cond
  ([oftype? type *string-type*]
   (weighted-choice *string*))
  ([ofsize? 'wint_t type] 'c)
  ([and (ofsize? 'char type) 
        (chance? 'actual-char)] 'c)
  ([ofsize? 'void* type] 'p)
  ([oftype? type *integer-type*]
    (weighted-choice 
     (if (signed? type) *signed-decimal* *unsigned-decimal*)))
  ([oftype? type *float-type*]
   (weighted-choice *floating-point*))
  (else (unreachable))
 )
)

(provide 
 fmt fmt? fmt-flags fmt-width fmt-precision fmt-length fmt-conversion
 takes-arg?
 fmt-precision->integer
 fmt-flags->string fmt-width->string fmt-precision->string fmt-length->string
 fmt-conversion->string
 fmt->string)

(struct fmt 
 (flags width precision length conversion) #:transparent)

(define (takes-arg? fmt)
 (not (eq? (fmt-conversion fmt) 'm)))

(define (fmt-flags->string fmt)
 (if [null? (fmt-flags fmt)] ""
  (fmt-flags fmt)))

(define (fmt-width->string fmt) 
 (if [null? (fmt-width fmt)] ""
  (format "~a" (fmt-width fmt))))

; Converts a fmt's precision field to an integer if the field
; is specified, and 'null' if it isn't specified.
(define (fmt-precision->integer fmt)
 (match (fmt-precision fmt)
  ['() '()]
  ['empty 0]
  [_ (fmt-precision fmt)]
 )
)

(define (fmt-precision->string fmt)
 (match (fmt-precision fmt)
  ['() ""]
  ['empty "."]
  [_ (format ".~a" (fmt-precision fmt))]
 )
)

(define (fmt-length->string fmt)
 (if [null? (fmt-length fmt)] ""
  (symbol->string (fmt-length fmt))))

(define (fmt-conversion->string fmt)
 (symbol->string (fmt-conversion fmt)))

(define (fmt->string fmt)
 (string-append "%"
  (fmt-flags->string fmt)
  (fmt-width->string fmt)
  (fmt-precision->string fmt)
  (fmt-length->string fmt)
  (fmt-conversion->string fmt)
 )
)

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
           (not (eq? conv 'c))
           ;(not (in? conv (no-weights *floating-point*)))
           (chance? 'space-flag)] " " "")
  (if [and (signed? type)
           (not (eq? conv 'c))
           ;(not (in? conv (no-weights *floating-point*)))
           (chance? 'sign-flag)] "+" "")
 )
)

(define (gen-width)
 (apply random-integer *field-width-range*))

(define (gen-precision type)
 (if (chance? 'precision-dotonly) 'empty
  (apply random-integer
   *precision-range*)))
   ;(if (oftype? type *float-type*) '(0 5) *precision-range*))))

(define (gen-fmt type)
 (let ([conv (type->conv-specifier type)])
  (if (in? conv *length-only*)
   (fmt null null null 
    ; M doesn't convert, so omit any applicable length spec.
    (if (eq? conv 'm) null 
     (type->length-specifier type)) conv)
   (fmt
    (if [and (not (eq? conv 's))
             (chance? 'format-flags)]
     (gen-flags type conv) null)
    (if (chance? 'format-width)
     (gen-width) null)
    ; Precision is not valid for character conversions
    (if [and (not (eq? conv 'c)) 
             (chance? 'format-precision)]
     (gen-precision type) null)
    ; Chars have a length specifier, but if we want print a char
    ; as an actual character we shouldn't include it.
    (if [and (eq? 'c conv) 
             (not (ofsize? 'wint_t type))] null
     (type->length-specifier type))
    conv
   )
  )
 )
)
