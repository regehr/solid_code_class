#lang racket

(require "weighted-random.rkt")
(provide (except-out (all-defined-out)
          char-range))

(define *pointer-bit-depth* 32)
(define *pointer-const-tail* "")

; 32-bit numeric-type bit-depths
(define *numeric-bit-depths* '(
 ("char" 8)
 ("short" 16)
 ("int" 32)
 ("long int" 32)
 ("long long int" 64)
 ("float" 32)
 ("double" 64)
 ("long double" 96)
))

;
(define (char-range start end)
 (map integer->char (range start (add1 end)))
)

; Vector of non-whitespace (except SPACE) characters not including
; ('), (") and (\).
(define *valid-characters* (list->vector
 (append (char-range 32 33) 
         (char-range 35 38) 
         (char-range 40 91)
         (char-range 93 126)))
)

; Non-Standard specifiers (as far as I can tell) : a A I

(define *signed-decimal*
 (uniformly-weighted '("d" "i")))
(define *unsigned-decimal*  
 (uniformly-weighted '("o" "u" "x" "X")))
(define *floating-point* 
 (uniformly-weighted '("e" "E" "f" "g" "G")))
(define *character* 
 (uniformly-weighted '("c")))
(define *c-string*
 (uniformly-weighted '("s")))
(define *pointer* 
 (uniformly-weighted (cons "p" (map cadr *unsigned-decimal*)))
)

(define *integer-types* '("char" "short" "int" "long int" "long long int"))
(define *float-types*   '("float" "double" "long double"))
(define *string-types*  '("char *"))

(define *datatype-signs*
 (uniformly-weighted '(
  "unsigned"
  "" ; signed
 ))
)

(define *datatype-sizes*
 (uniformly-weighted 
  (append *integer-types* *float-types* *string-types*))
)

