#lang racket

(require "common.rkt")
(require "chance.rkt")
(require "random-extra.rkt")

(provide
 *integer-type* *float-type* *string-type*)

(define *integer-type* 
 '(char wint_t short int long-int long-long-int
   ptrdiff_t size_t ssize_t intmax_t uintmax_t
   void*))
(define *float-type*   '(float double long-double))
(define *string-type*  '(char* wchar_t*))

(define *type-sizes* 
 (uniformly-weighted 
  (append *integer-type* *float-type* *string-type*)
  ;(append *integer-type* *string-type*)
))

(define *type-signs*
 (uniformly-weighted '(signed unsigned)))

(define *string-length-range* '(5 50))

; All of these types don't need a sign, because their sign is
; implicit in their definition.
(define *implicit-sign*
 '(void* ptrdiff_t size_t ssize_t intmax_t uintmax_t))

; Evaluates a list of characters in the range [start, end]
(define (char-range start end)
 (map integer->char (range start (add1 end))))

; Vector of non-whitespace (except SPACE) characters not including
; ('), (") and (\).
(define *valid-characters* (list->vector
 (append (char-range 32 33) 
         (char-range 35 36) 
         (char-range 38 38) 
         (char-range 40 91)
         (char-range 93 126))))

; 32-bit numeric-type bit-depths
(define *bit-widths* '(
 ; Standard types
 (char 8)
 (short 16)
 (int 32)
 ; See comment below on compatability.
 (long-int 32)
 (long-long-int 64)
 (float 32)
 (double 64)
 (long-double 96)
 (void* 32)
 ; Wide character
 (wint_t 32)
 ; Less-used types
 (intmax_t  64)
 (uintmax_t 64)
 ; These types are 8 bytes on LP64, but I'm keeping them
 ; at 32 bits to maintain compatability with ILP32.
 (ptrdiff_t 32)
 (size_t 32)
 (ssize_t 32)
))

; Map an integer's size to it's signed-ness. If the type can be
; signed or unsigned, 'default' is returned.
(define (integer-size->sign size default)
 (match size
  ['void* 'unsigned]
  ['intmax_t 'signed]
  ['uintmax_t 'unsigned]
  ['ptrdiff_t 'signed]
  ['size_t 'unsigned]
  ['ssize_t 'signed]
  [_ default]
 )
)

; Interface 
(provide
 type type? type-size ofsize? signed? oftype? type-name
 type-value type-bit-width type-postfix
 type-size->string type-value->string type-name->string
 type->string type-assignment->string)

(struct type 
 (signed? size name gen writer) #:transparent)

(define (signed? type) 
 (eq? 'signed (type-signed? type)))

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
   ['intmax_t      "LL"]
   ['uintmax_t     "LL"]
   ['float         "F"]
   ['long-double   "L"]
   [_ ""]
  )
 )
)

(define (type-size->string type [strip-pointer? #f])
 (let ([halfway (string-replace 
                 (symbol->string (type-size type)) "-" " ")])
  (if strip-pointer? 
   (string-replace halfway "*" "")
   halfway)
 )
)

(define (type-value type)
 ((type-gen type) type))

(define (type-name->string type)
 (symbol->string (type-name type)))

(define (type-value->string type)
 ((type-writer type) type))

(define (type->string type [string-pointer? #f])
 (string-append
  (cond
   ([signed? type] "")
   ([in? (type-size type) *implicit-sign*] "")
   (else "unsigned "))
  (type-size->string type string-pointer?)))

(define (type-assignment->string type)
 (string-append
  (if [ofsize? 'void* type]
   (type->string type)
   (type->string type #t))
  " "
  (type-name->string type)
  (if [oftype? type *string-type*] "[]" "")
  " = "
  (type-value->string type)
  ";"))

; **** Value Writers ****

(define (integer-writer type)
 (string-append
  "(" (type->string type) ") "
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
 (string-append 
  (if [ofsize? 'wchar_t* type] "L" "") 
  "\"" (apply string (type-value type)) "\""))

(define (char-writer type)
 (string-append
  (if [ofsize? 'wint_t type] "L" "")
  "'" (string (type-value type)) "'"))

; Generation

(provide gen-type)

(define (gen-string type)
 (define (_gen-string len)
  (if (= len 0) '()
   (cons (vector-pick *valid-characters*)
    (_gen-string (sub1 len)))
  )
 )
 (_gen-string (apply random-integer *string-length-range*)))

; Generate a random real floating-point number.
(define (gen-float type)
 (cond
  ([chance? 'gen-nan]
   (if (< 0.5 (random-real 0 1)) +nan.0 -nan.0))
  ([chance? 'gen-inf]
   (if (< 0.5 (random-real 0 1)) +inf.0 -inf.0))
  (else
   (let ([bytes (/ (type-bit-width type) 8)])
    (floating-point-bytes->real
     (if (< bytes 8) (random-bytes 4) (random-bytes 8))))
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

(define (gen-char type)
 (vector-pick *valid-characters*))

(define (gen-type)
 (let* ([sign (weighted-choice *type-signs*)]
        [size (weighted-choice *type-sizes*)]
        [var-name (gensym)])
  ; Float types can't be unsigned, so make sure we only set the sign-value
  ; for integer types.
  (cond
   ([in? size *float-type*] 
    (type 'signed size var-name gen-float float-writer)) 
   ([in? size *string-type*]
    (type 'signed size var-name gen-string string-writer))
   ([eq? size 'wint_t]
    (type 'signed size var-name gen-char char-writer))
   ([in? size *integer-type*]
    (type (integer-size->sign size sign) 
     size var-name gen-integer integer-writer))
   (else (unreachable))
  )
 )
)
