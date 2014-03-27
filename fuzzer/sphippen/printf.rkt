(module printf racket

  (require (only-in math/base random-integer))
  (require "generate.rkt")

  (provide generate-printf)

  (define char-max 10)
  (define conv-max 10)

  (define (generate-printf)
    (let* ([n-char (random-integer 0 (+ char-max 1))]
           [chars (generate-chars n-char)]
           [n-conv (random-integer 0 (+ conv-max 1))]
           [convs (generate-convs n-conv)])
      (shuffle (append chars convs))))

  (define (generate-chars n)
    (build-list n (lambda (n) (generate-sl-char))))
  
  (define (generate-convs n)
    (build-list n (lambda (n) (generate-conv))))

  (struct conv
    (char-lst   ; list of bare conversion characters
     length-lst ; list of applicable length modifiers paired with generation functions
     precision  ; #t if precision flag is applicable, #f otherwise
     flags))    ; list of valid flags

  (define int-length-lst '(hh h l ll j))

  (define conversions
    `(,(conv '(d i)
             int-length-lst
             #t
             '(0 - | | +))

      ,(conv '(u)
             int-length-lst
             #t
             '(0 - | | +))

      ,(conv '(o x X)
             int-length-lst
             #t
             '(|#| 0 - | | +))

      ,(conv '(a A e E f F g G)
             '() ; TODO: (?) investigate '(L) weirdness in gcc
             #t
             '(|#| 0 - | | +))

      ,(conv '(c)
             '(l)
             #f
             '())

      ,(conv '(s)
             '() ; TODO: (?) get '(L) to work (lots of bad things in musl currently)
             #f
             '())
      ,(conv '(%)
             '()
             #f
             '())))
; TODO: add n flag for writing out "chars printed so far", p for void* as hex

; TODO: generate width fields (remember '*' option)
; TODO: generate precision fields (remember '*' option)
  (define (generate-conv)
    (define conv (pick-from conversions))
    (define char (pick-from (conv-char-lst conv)))
    (define lenmod (pick-from (cons '|| (conv-length-lst conv))))
    (define value (generate-value char lenmod))

    ; go from symbols to strings for output
    (define conv-str (string-append (symbol->string lenmod)
                                    (symbol->string char)))
    (if (void? value)
      (list conv-str)
      (list conv-str value)))

)
