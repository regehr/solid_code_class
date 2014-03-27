(module generate racket

  (require (only-in math/base random-integer random-natural))

  (provide pick-from generate-sl-char generate-value)

  (define (pick-from lst)
    (let ([index (random-natural (length lst))])
      (list-ref lst index)))

  (define (generate-sl-char)
    (let* ([pre-byte (random-integer 33 126)] ; Generate a byte in [33, 125] (don't want non-printable char in the string literal)
           [byte (if (>= pre-byte 37) (+ pre-byte 1) pre-byte)] ; Shift to get a byte in [33, 36] U [38, 126] to avoid '%' char
           [out (open-output-string)])
      (fprintf out "\\x~x" byte)
      (get-output-string out)))

  (define (generate-value char lenmod)
    (match char
      [(or 'd 'i)
       (match lenmod
         ['|| (gen-in -32767 32767)] ; int
         ['hh (gen-in -127 127)] ; signed char
         ['h  (gen-in -32767 32767)] ; short
         ['l  (gen-in -2147483647 2147483647 "L")] ; long
         ['ll (gen-in -9223372036854775807 9223372036854775807 "LL")] ; long long
         ['j  (gen-in -9223372036854775807 9223372036854775807 "LL" #:cast "intmax_t")])] ; intmax_t

      [(or 'u 'o 'x 'X)
       (match lenmod
         ['|| (gen-in 0 65535)] ; unsigned
         ['hh (gen-in 0 255)] ; unsigned char
         ['h  (gen-in 0 65535)] ; unsigned short
         ['l  (gen-in 0 4294967295 "UL")] ; unsigned long
         ['ll (gen-in 0 18446744073709551615 "ULL")] ; unsigned long long
         ['j  (gen-in 0 18446744073709551615 "ULL" #:cast "uintmax_t")])] ; uintmax_t

      [(or 'f 'F 'e 'E 'g 'G 'a 'A)
       (match lenmod
         ['|| (gen-double)]
         ['L  (gen-long-double)])]

      ['c
       (match lenmod
         ['|| (gen-in 33 126)] ; int (but print as char) - only normal printing characters here
         ['l  (gen-in 33 126 #:cast "wint_t")])] ; wint_t - TODO: expand this?

      ['s
       (match lenmod
         ['|| (gen-str)]
         ['L  (string-append "L" (gen-str))])]

      ['% (void)]))

  (define (gen-in bottom top [suffix ""] #:cast [cast ""])
    (define cast-str (if (eq? cast "")
                       ""
                       (string-append "(" cast ")")))
    (define value (number->string
                    (random-integer bottom (+ top 1))))
    (string-append cast-str value suffix))

  (define (gen-str)
    "\"hello, world!\"") ; TODO: expand

  (define (gen-double)
    (match (random-integer 0 1000)
      [0 "INFINITY"]
      [1 "NAN"]
      [_ (gen-number-double)]))

  (define (gen-long-double)
    (string-append "(long double)" (gen-double))) ; TODO - better coverage here

  (define (gen-number-double)
    (number->string
      (* 1e300 (- (random) 0.5)))) ; TODO: better coverage here

)
