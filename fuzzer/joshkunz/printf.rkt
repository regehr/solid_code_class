#lang racket

(require "common.rkt")
(require "random-extra.rkt")
(require "types.rkt")
(require "format.rkt")
(require "chance.rkt")

(define *printf-arg-range* '(1 5))

(define *printf-prelude* (string->bytes/utf-8
"#include <stdio.h>
#include <math.h>
#include <wchar.h>
#include <stdint.h>
#include <stddef.h>
  
#ifdef MUSL
#include \"musl.h\"
#define snprintf musl_snprintf
#endif

#define BUFFER_LEN 10000
char buffer[BUFFER_LEN] = { 0 };

int main() {\n"))

(define *printf-epilogue* (string->bytes/utf-8
"    return 0;
}\n"))

; Unzip a list of pairs '(a . b) into two seperate lists '((a) (b)).
(define (unzip-pairs pairs)
 (if (null? pairs) '(() ())
  (let ([next (unzip-pairs (cdr pairs))])
   (list 
    (cons (caar pairs) (car next))
    (cons (cdar pairs) (cadr next)))
  )
 )
)

; **** Formatting Helpers ****

(define (fmt-pair->arg-string fmt-pair)
 (let ([conv (fmt-conversion (car fmt-pair))]
       [type (cdr fmt-pair)])
  (string-append
   (if [eq? conv 'n] "&" "")
   (if [eq? conv 'm] ""
    (type-name->string type))
  )
 )
)

(define (fmt-pair->fmt-list fmt-pair)
 (let* ([fmt (car fmt-pair)]
        [type (cdr fmt-pair)]
        [width (fmt-width fmt)] 
        [width? (not (null? width))]
        [prec (fmt-precision->integer fmt)]
        [prec? (not (null? prec))])
  (list fmt type width width? prec prec?)))

; Return a pair of strings
(define (fmt-pair->string-pair/star fmt-pair)
 (let-values ([(fmt type width width? prec prec?)
               (apply values (fmt-pair->fmt-list fmt-pair))])
  (cons
   (string-append "%"
    (fmt-flags->string fmt)
    (if width? "*" (fmt-width->string fmt))
    (if prec? ".*" (fmt-precision->string fmt))
    (fmt-length->string fmt)
    (fmt-conversion->string fmt))
   (string-join
    (filter-not string-empty?
     (list (if width? (number->string width) "")
           (if prec? (number->string prec) "")
           (fmt-pair->arg-string fmt-pair))) ", ")
  )
 )
)

(define (fmt-pair->positional-pair fmt-pair)
 ; Evalutates to the given integer as a string post-fixed with a dollar.
 (define (darg v) 
  (string-append (number->string v) "$"))
 (let-values ([(fmt type width width? prec prec?)
               (apply values (fmt-pair->fmt-list fmt-pair))])
  (cons
   (list "%"
    (if [takes-arg? fmt] (lambda (i) (darg i)) "")
    (fmt-flags->string fmt)
    (if width? (lambda (i) (string-append "*" (darg i))) "")
    (if prec? 
     (lambda (i) (string-append ".*" (darg i))) "")
    (fmt-length->string fmt)
    (fmt-conversion->string fmt))
   (filter-not void?
    (list
     ; The conversion spec arg needs to go first because the algorithm assumes
     ; that the lambdas are in the same order as the arguments.
     (when (takes-arg? fmt) 
      (fmt-pair->arg-string fmt-pair))
     (when width? (number->string width))
     (when prec? (number->string prec))))
  )
 )
)

(define (resolve-group/positional arg-map)
 (lambda (next fold)
  (let-values ([(index group-string) (apply values fold)])
   (cond
    ([procedure? next]
     (list (add1 index) 
      (string-append group-string 
       ; We have to add 1 because assf-index is 0-indexed and
       ; printf is 1 indexed.
       (next (add1 (assf-index eq? index arg-map))))))
    ([string? next]
     (list index (string-append group-string next)))
   )
  )
 )
)
 
(define (resolve-args/positional fmt-lists arg-map [index 1])
 (if [null? fmt-lists] '()
  (let-values ([(next-index group-string) 
                (apply values 
                 (foldl (resolve-group/positional arg-map)
                  (list index "") (car fmt-lists)))])
   (cons group-string 
    (resolve-args/positional (cdr fmt-lists) arg-map next-index)))
 )
)


; **** Formatters ****

(define (fmt-pairs->string/standard fmt-pairs)
 (let ([formats (map car fmt-pairs)]
       [args (filter-not string-empty? (map fmt-pair->arg-string fmt-pairs))])
  (list
   (string-join (map fmt->string formats) "")
   (if (= (length args) 0) ""
    (string-join args ", "))
  )
 )
)

(define (fmt-pairs->string/star fmt-pairs)
 (let ([groups (unzip-pairs 
                (map fmt-pair->string-pair/star fmt-pairs))])
  (list
   (string-join (car groups) "")
   (string-join (filter-not string-empty? (cadr groups)) ", "))))

(define (fmt-pairs->string/positional fmt-pairs) 
 (let* ([groups (unzip-pairs (map fmt-pair->positional-pair fmt-pairs))]
        ; Flatten automagically removes empty lists for us.
        [arg-map (shuffle (enumerate (flatten (cadr groups))))]
        [formats (shuffle (resolve-args/positional (car groups) arg-map))])
  (list 
   (string-join formats "")
   (string-join (map cadr arg-map) ", ")
  )
 )
)

(define *formatters*
 (uniformly-weighted 
  (list 
   fmt-pairs->string/standard 
   fmt-pairs->string/star
   fmt-pairs->string/positional)))

(define (fmt-pairs->string fmt-pairs)
 (apply values 
  (cons (string-join 
         (map type-assignment->string (map cdr fmt-pairs))
         "\n    " #:after-last "\n")
   ((weighted-choice *formatters*) fmt-pairs))))

; **** Generation ****

(define (gen-fmt-pairs count)
 (if (= count 0) '()
  (let ([type (gen-type)])
   (cons
    (cons (gen-fmt type) type)
    (gen-fmt-pairs (sub1 count)))
  )
 )
)

; Generate a string printf statement with 'spec-count' vars printed.
(define (gen-printf spec-count)
 (let-values ([(assignment sformat svalue)
               (fmt-pairs->string (gen-fmt-pairs spec-count))])
  (string-append
   assignment
   "    snprintf(buffer, BUFFER_LEN, \"" 
   sformat
   "\\n\""   ; Make sure that all format strings end with '\n' for easier
             ; debugging.
   (if (string-empty? svalue) 
    "" ", ")
   svalue
   "); fputs(buffer, stdout);"
  )
 )
)

; **** Stream Interface ****

(provide printf-stream)

(struct printf-stream
 (count print-prelude?)
 #:methods gen:stream
 [(define (stream-empty? stream)
   (<= (printf-stream-count stream) 0))
  (define (stream-first stream)
   (bytes-append
    (if (printf-stream-print-prelude? stream) *printf-prelude* #"")
    #"    " ; Formatting counts
    (string->bytes/utf-8 
     (gen-printf (apply random-integer *printf-arg-range*)))
    #"\n"
    (if (= (printf-stream-count stream) 1) *printf-epilogue* #"")
   )
  )
  (define (stream-rest stream)
   (printf-stream
    (sub1 (printf-stream-count stream)) #f)
  )]
)
