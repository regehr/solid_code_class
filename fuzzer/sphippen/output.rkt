(module output racket

  (provide printfs-to-file)

  (define (printfs-to-file lst file)
    (let ([str (printfs-to-file-string lst)]
          [out-f (open-output-file file #:mode 'binary #:exists 'truncate)])
      (display str out-f)
      (close-output-port out-f)))

  (define (printfs-to-file-string lst)
    (let ([start "#include <stdio.h>\nint main(int argc, char* argv[]) {\nFILE* out = fopen(\"out.bin\", \"w\");\n"]
          [end "fclose(out);\nreturn 0;\n}"])
      (string-append (for/fold ([str start])
                       ([printf lst])
                       (string-append str (printf->string printf)))
                     end)))

  (define (printf->string printf)
    (define (work args format c-args)
      (if (empty? args)
        (string-append "fprintf(out, \"" format "\"" c-args ");\n")
        (let* ([rest (cdr args)]
               [arg (car args)]
               [is-conv (list? arg)]
               [new-format (if is-conv
                             (string-append format "%" (car arg))
                             (string-append format arg))]
               [new-c-args (if (and is-conv
                                    (not (null? (cdr arg))))
                             (string-append c-args ", " (cadr arg))
                             c-args)])
          (work rest new-format new-c-args))))
    (work printf "" ""))

)
