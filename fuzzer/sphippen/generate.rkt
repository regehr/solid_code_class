(module generate racket

  (require (only-in math/base random-integer random-natural))

  (provide pick-from gen-sl-char gen-int gen-unsigned)

  (define (pick-from lst)
    (let ([index (random-natural (length lst))])
      (list-ref lst index)))

  (define (gen-sl-char)
    (let ([byte (random-integer 1 128)] ; generate in [1, 127] - no embedded nulls in string literals
          [out (open-output-string)])
      (fprintf out "\\x~x" byte)
      (get-output-string out)))

  (define (gen-int)
    (number->string
      (random-integer -32767 32768)))

  (define (gen-unsigned)
    (number->string
      (random-natural 65536)))

)
