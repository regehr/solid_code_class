(module minimize racket

  (provide minimize)

  ; Given a set of printfs that generate different outputs, attempts
  ; to minimize the set of printfs and things in each printf, returning
  ; the minimized version.
  (define (minimize printfs printf-zero-diff?)
    (define (min-single printf)
      (define len (length printf))
      (if (= len 1)
        printf
        (let-values ([(start end) (split-at printf (quotient len 2))])
          (cond
            [(not (printf-zero-diff? (list start))) (min-single start)]
            [(not (printf-zero-diff? (list end))) (min-single end)]
            [else printf]))))

    (define (min printfs)
      (define len (length printfs))
      (if (= len 1)
        (list (min-single (car printfs)))
        (let-values ([(start end) (split-at printfs (quotient len 2))])
          (cond
            [(not (printf-zero-diff? start)) (min start)]
            [(not (printf-zero-diff? end)) (min end)]
            [else printfs]))))

    (min printfs))

)
