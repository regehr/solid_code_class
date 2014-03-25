(module printf racket

  (require (only-in math/base random-integer))
  (require "generate.rkt")

  (provide gen-printf)

  (define char-max 10)
  (define conv-max 10)

  (define (gen-printf)
    (let* ([n-char (random-integer 0 (+ char-max 1))]
           [chars (gen-chars n-char)]
           [n-conv (random-integer 0 (+ conv-max 1))]
           [convs (gen-convs n-conv)])
      (shuffle (append chars convs))))

  (define (gen-chars n)
    (build-list n (lambda (n) (gen-sl-char))))
  
  (define (gen-convs n)
    (build-list n (lambda (n) (gen-conv))))

  (define conversions
    `((,gen-int (d i)) ; int
      (,gen-unsigned (o u x X)) ; unsigned
;      e E ; sci notation double
;      f F ; normal notation double
;      g G ; shorter of e/f or E/F respectively
;      a A ; hex double notation
;      c ; char
;      s ; string
;      p ; void* as hex
;      n ; write number of chars written so far to int* arg
      (,(void) (%)) ; percent char
      ))

  (define (gen-conv)
    (let* ([type (pick-from conversions)]
           [char (pick-from (cadr type))]
           [gen (car type)])
      (if (void? gen)
        (list (symbol->string char))
        (list (symbol->string char) (gen)))))

)
