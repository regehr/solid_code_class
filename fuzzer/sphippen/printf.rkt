(module printf racket

  (require "generate.rkt")

  (provide gen-printf)

  (define char-max 1000)
  (define conv-max 1000)

  (define (gen-printf)
    (let* ([n-char (random char-max)]
           [chars (gen-chars n-char)]
           [n-conv (random conv-max)]
           [convs (gen-convs n-conv)])
      (shuffle (append chars convs))))

  (define (gen-seq n gen)
    (define (work n lst)
      (match n
        [0 lst]
        [_ (let ([val (gen)])
             (work (- n 1) (cons val lst)))]))
    (work n '()))

  (define (gen-chars n)
    (gen-seq n gen-sl-char))
  
  (define (gen-convs n)
    (gen-seq n gen-conv))

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
