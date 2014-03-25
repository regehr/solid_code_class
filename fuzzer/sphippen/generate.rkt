(module generate racket

  (require (only-in math/base random-integer random-natural))

  (provide pick-from gen-sl-char gen-int gen-unsigned)

  (define (pick-from lst)
    (let ([index (random-natural (length lst))])
      (list-ref lst index)))

  (define (gen-sl-char)
    (let* ([pre-byte (random-integer 1 127)] ; Generate a byte in [1, 126] (don't want a null char in the string literal)
           [byte (if (>= pre-byte 37) (+ pre-byte 1) pre-byte)] ; Shift to get a byte in [1, 36] U [38, 127] to avoid '%' char
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
