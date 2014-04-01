(module printf racket

  (require (only-in math/base random-integer))
  (require "generate.rkt")

  (provide generate-printf (struct-out pf-spec))

  (struct pf-spec
    (conv        ; string containing conversion specifier
     value-lst   ; list of values (may be multiple for width/precision)
     prologue    ; code to go before call (only once, even if multiple calls are made)
     epilogue))  ; printf call to go after call (for each call), i.e. a list of pf-specs or void if not applicable

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
    (char-lst    ; list of bare conversion characters
     length-lst  ; list of applicable length modifiers paired with generation functions
     precision   ; #t if precision flag is applicable, #f otherwise
     flags-lst)) ; list of valid flags

  (define int-length-lst '(hh h l ll j))

  (define conversions
    `(,(conv '(d i)
             int-length-lst
             #t
             '(|0| - | | +))

      ,(conv '(u)
             int-length-lst
             #t
             '(|0| -))

      ,(conv '(o x X)
             int-length-lst
             #t
             '(|#| |0| -))

      ,(conv '(a A e E f F g G)
             '(L) ; TODO: (?) investigate '(L) weirdness in gcc
             #t
             '(|#| |0| - | | +))

      ,(conv '(c)
             '(l)
             #f
             '())

      ,(conv '(s)
             '(l)
             #t
             '())

      ,(conv '(p)
             '()
             #f
             '(- | | +))

      ,(conv '(%)
             '()
             #f
             '())))
; TODO: add n flag for writing out "chars printed so far"

  (define (generate-conv)
    (define conv (pick-from conversions))
    (define char (pick-from (conv-char-lst conv)))
    (define lenmod (pick-from (cons '|| (conv-length-lst conv))))
    (define flags-list ; Select a subset of flags
      (letrec ([work (lambda (lst accum)
                       (cond
                         [(null? lst) accum]
                         [(= 0 (random 2))
                          (work (cdr lst) (cons (car lst) accum))]
                         [(work (cdr lst) accum)]))])
        (work (conv-flags-lst conv) '())))

    (define value (generate-value char lenmod))

    (define width
      (if (and (not (void? value))
               (= (random-integer 0 2) 0))
        (let ([base (random-integer 0 2)])
          (match base
            [0 "*"]
            [_ (generate-w/p)]))
        ""))

    (define width-value
      (if (equal? width "*")
        (generate-w/p)
        (void)))

    (define precision
      (if (and (not (void? value))
               (conv-precision conv)
               (= (random-integer 0 2) 0))
        (string-append "."
          (let ([base (random-integer 0 3)])
            (match base
              [0 "*"]
              [1 ""]
              [_ (generate-w/p)])))
        ""))

    (define precision-value
      (if (equal? precision ".*")
        (generate-w/p)
        (void)))

    (define value-lst '())

    (for ([i `(,value ,precision-value ,width-value)])
      (if (not (void? i))
        (set! value-lst (cons i value-lst))
        (void)))

    ; go from symbols to strings for output
    (define conv-str (string-append (apply string-append (map symbol->string flags-list))
                                    width
                                    precision
                                    (symbol->string lenmod)
                                    (symbol->string char)))

    (pf-spec conv-str value-lst "" (void)))

)
