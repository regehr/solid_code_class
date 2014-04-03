(module printf racket

  (require (only-in math/base random-integer))
  (require "generate.rkt" srfi/1)

  (provide generate-printf (struct-out pf-spec))

  (define n-count 0)

  (struct pf-spec
    (conv        ; string containing conversion specifier
     value-lst   ; list of values (may be multiple for width/precision)
     prologue    ; code to go before call (only once, even if multiple calls are made)
     epilogue))  ; printf call to go after call (for each call), i.e. a list of pf-specs or void if not applicable

  (define char-max 10)
  (define conv-max 10)

  (define (interleave l1 l2)
    (define (work l1 l2 accum)
      (cond
        [(null? l1) (append (reverse accum) l2)]
        [(null? l2) (append (reverse accum) l1)]
        [(= 0 (random-integer 0 2))
         (work (cdr l1) l2 (cons (car l1) accum))]
        [else (work l1 (cdr l2) (cons (car l2) accum))]))
    (work l1 l2 '()))

  (define (generate-printf)
    (let* ([n-char (random-integer 0 (+ char-max 1))]
           [chars (generate-chars n-char)]
           [n-conv (random-integer 0 (+ conv-max 1))]
           [convs (generate-convs n-conv)])
      (interleave chars convs)))

  (define (generate-chars n)
    (build-list n (lambda (n) (generate-sl-char))))
  
  (define (star-replace str ords)
    (define (work str ords acc)
      (cond
        [(= (string-length str) 0)
         (values acc ords)]
        [(equal? #\* (string-ref str 0))
         (work (substring str 1)
               (cdr ords)
               (string-append acc "*" (number->string (+ 1 (car ords))) "$"))]
        [else (work (substring str 1)
                    ords
                    (string-append acc (substring str 0 1)))]))
    (work str ords ""))

  (define (reref spec off ord)
    (define spec-len (length (pf-spec-value-lst spec)))
    (define old-refs (map (lambda (n) (+ n off)) (range spec-len)))
    (define new-refs (map (lambda (n) (list-index (lambda (m) (= n m)) ord))
                          old-refs))

    (define new-conv
      (let-values ([(starred leftover)
                  (star-replace (pf-spec-conv spec) new-refs)])
      (if (null? leftover)
        starred
        (let ()
          (unless (null? (cdr leftover))
            (error "more than one leftover!"))
          (string-append (number->string (+ (car leftover) 1)) "$" starred)))))

    (define new-spec (struct-copy pf-spec spec [conv new-conv]))
    (values new-spec (+ off spec-len)))

  (define (swap-in spec ord args)
    (define (work vals ord acc)
      (if (null? vals)
        (values (reverse acc) ord)
        (let* ([next-val (list-ref args (car ord))])
          (work (cdr vals) (cdr ord) (cons next-val acc)))))
    (let-values ([(new-vals new-ord)
                  (work (pf-spec-value-lst spec) ord '())])
      (define vals-spec (struct-copy pf-spec spec [value-lst new-vals]))
      (values vals-spec new-ord)))

  (define (move-args raw ord args)
    (define (conv-args raw ord acc)
      (if (null? raw)
        (reverse acc)
        (let ([spec (car raw)])
          (let-values ([(new-spec new-ord)
                        (swap-in spec ord args)])
            (conv-args (cdr raw) new-ord (cons new-spec acc))))))

    (define (conv-refs raw off acc)
      (if (null? raw)
        (reverse acc)
        (let ([spec (car raw)])
          (let-values ([(new-spec new-off)
                        (reref spec off ord)])
            (conv-refs (cdr raw) new-off (cons new-spec acc))))))

    (conv-refs (conv-args raw ord '()) 0 '()))

  (define (generate-convs n)
    (define raw (build-list n (lambda (n) (generate-conv))))
    
    ; Positional args
    (define args (for/fold ([lst '()])
                   ([conv raw])
                   (append lst (pf-spec-value-lst conv))))

    (if (> (length args) 10) ; There can only be 9 positional arguments, but we will test with 10 as well for coverage
      raw
      (let ()
        (define ord (shuffle (range (length args))))
        (move-args raw ord args))))

  (struct conv
    (char-lst    ; list of bare conversion characters
     length-lst  ; list of applicable length modifiers paired with generation functions
     precision   ; #t if precision flag is applicable, #f otherwise
     flags-lst)) ; list of valid flags

  (define int-length-lst '(hh h l ll j z))

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
             '(-))

      ,(conv '(m)
             '()
             #f
             '())

      ,(conv '(S)
             '()
             #t
             '())

      ,(conv '(C)
             '()
             #f
             '())

      ,(conv '(n)
             int-length-lst
             #f
             '())

      ,(conv '(%)
             '()
             #f
             '())))

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
               (not (equal? char 'n)) ; special case
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

    (define prologue "")
    (define epilogue (void))

    ; go from symbols to strings for output
    (define conv-str (string-append (apply string-append (map symbol->string flags-list))
                                    width
                                    precision
                                    (symbol->string lenmod)
                                    (symbol->string char)))

    ; n specifier special case
    (if (equal? char 'n)
      (let ([var-name (string-append "nvar" (number->string n-count))])
        (let-values ([(pro val) (generate-n-values var-name lenmod)])
          (set! n-count (+ 1 n-count))
          (set! value val)
          (set! prologue pro)
          (set! epilogue `(,(pf-spec (string-append (symbol->string lenmod) "d")
                                     (list var-name)
                                     ""
                                     (void))))))
      (void))

    (define value-lst '())

    (for ([i `(,value ,precision-value ,width-value)])
      (if (not (void? i))
        (set! value-lst (cons i value-lst))
        (void)))

    (pf-spec conv-str value-lst prologue epilogue))

)
