(module minimize racket

  (provide minimize)

  ; Given a set of printfs that generate different outputs, attempts
  ; to minimize the set of printfs, returning the minimized version.
  ; It used to also minimize the individual printf, but that got
  ; a lot more tricky with positional arguments
  (define (minimize printfs printf-zero-diff?)
    (define (min printfs)
      (define len (length printfs))
      (if (= len 1)
        printfs
        (let-values ([(start end) (split-at printfs (quotient len 2))])
          (cond
            [(not (printf-zero-diff? start)) (min start)]
            [(not (printf-zero-diff? end)) (min end)]
            [else printfs]))))

    (min printfs))

)
