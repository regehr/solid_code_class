(module compare racket

  (require "output.rkt")
  (require "minimize.rkt")

  (provide test-printfs setup)

  (define fuzz-src-name "fuzz.c")

  (define gcc (find-executable-path "gcc"))
  (define cmp (find-executable-path "cmp"))
  (define coverage-flags '("-fprofile-arcs" "-ftest-coverage"))

  (define (compile out objs [args '()])
    (if (apply system* `(,gcc ,@args ,"-o" ,out ,@objs))
      #t
      (raise-user-error 'compile "Couldn't compile to ~a.~%" out)))

  (define (compile-o src-name [args '()])
    (if (apply system* `(,gcc ,@args ,"-c" ,src-name))
      #t
      (raise-user-error 'compile-o "Couldn't compile .o from ~a.~%" src-name)))

  (define (printf-zero-diff? printfs)
    ; Create source file
    (printfs-to-file printfs fuzz-src-name)

    ; Compile files
    (compile-o fuzz-src-name)
    (compile "fuzz"
             '("fuzz.o" "fwrite.o" "snprintf.o" "vfprintf-fixed.o" "vsnprintf.o")
             coverage-flags)
    (system* "fuzz")

    ; Run the diff
    ; I don't know of a better way to scrap the error and output data than this
    (parameterize ([current-error-port (open-output-string)]
                   [current-output-port (open-output-string)])
      (= (system*/exit-code cmp "musl.bin" "glibc.bin") 0)))

  (define (setup)
    (void
      (compile-o "../musl-printf-standalone/fwrite.c")
      (compile-o "../musl-printf-standalone/snprintf.c")
      (compile-o "vfprintf-fixed.c" coverage-flags)
      (compile-o "../musl-printf-standalone/vsnprintf.c")))

  (define (test-printfs printfs diff-count)
    (if (printf-zero-diff? printfs)
      #t
      (begin ; Save source that triggers differences
        (printf "Difference found: minimizing...~%")
        (let ([err-src-name (string-append "diff" (number->string (+ diff-count 1)) ".c")]
              [minimized (minimize printfs printf-zero-diff?)])
          (printfs-to-file minimized err-src-name #f)
          (printf "Minimized case saved in ~a~%" err-src-name)
          #f))))

)
