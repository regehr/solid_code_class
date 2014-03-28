#lang racket 

(provide
 make-color make-style 
 color style
 compiled-style? compiled-color?
 make-printfs make-formats)

(define *color-bases* 
 '((foreground 30)
   (background 40)))

(define *colors*
 '((black   0)
   (red     1)
   (green   2)
   (yellow  3)
   (blue    4)
   (magenta 5)
   (cyan    6)
   (white   7)))

(define *styles*
 '((bright    1)
   (underline 4)
   (italic    3)
   (negative  7)))

; Assoc helper that returns the second item
; in a pair found via assoc
(define (assocv v lst)
 (let ([found (assoc v lst)])
  (if found (cadr found) #f)
 )
)

; Returns #t when 'v' is a compiled color
(define (compiled-color? v)
 (and (pair? v) 
      (eq? (car v) 'compiled-color)))

; Returns #t when 'v' is a compiled style
(define (compiled-style? v)
 (and (pair? v) 
      (eq? (car v) 'compiled-style))
)

(define (make-color color-name [intensity 'normal] [ground 'foreground])
 (let* ([color-num (+ (assocv ground *color-bases*)
                      (assocv color-name *colors*))]
        [color-num-string (number->string color-num)])
  `(compiled-color
    ,(string-append
      (if (eq? intensity 'bright) 
       (string-append (number->string (assocv intensity *styles*)) ";") "")
      color-num-string "m")
   )
 )
)

; Convert a style symbol (or compiled sytle) into a string
(define (style->string style)
 (cond
  [(or (compiled-style? style)
       (compiled-color? style)) (cadr style)]
  [else (number->string (assocv style *styles*))]
 )
)

; Compile the list of styles into a compiled style string
(define (make-style . styles)
 `(compiled-style
   ,(string-join (map style->string styles) ";"))
 )

; Return colored text
(define (color str color-name [intensity 'normal] [ground 'foreground])
 (style str (make-color color-name intensity ground)))

; Return the styled text 
(define (style str . styles)
 (string-append "\e[" (style->string (apply make-style styles)) str "\e[0m")
)

; return a printf function that will printf with the given styles
(define (make-printfs . styles)
 (let ([formats (apply make-formats styles)])
  ; Lambdas can't have a . rest-id unless they have at least one argument.
  (lambda ( #:dummy [x #t] . fmt)
   (display (apply formats fmt))
  )
 )
)

; returns a 'format' function that will format the text with the given
; styles.
(define (make-formats . styles)
 (lambda ( #:dummy [x #t] . fmt)
  (apply style (apply format fmt) styles)
 )
)
