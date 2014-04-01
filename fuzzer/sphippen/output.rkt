(module output racket

  (provide printfs-to-file)

  (define (printfs-to-file lst file [cov #t])
    (define converter (if cov cov-printfs-to-file-string printfs-to-file-string))
    (let ([str (converter lst)]
          [out-f (open-output-file file #:mode 'binary #:exists 'truncate)])
      (display str out-f)
      (close-output-port out-f)))

  (define cov-prologue (string-append
"#include <stdio.h>\n"
"#include <math.h>\n"
"#include <stdint.h>\n"
"#include <wchar.h>\n"
"#include \"../musl-printf-standalone/musl.h\"\n"
"\n"
"#define LEN 1000000\n"
"char buf[LEN];\n"
"\n"
"int main(int argc, char* argv[]) {\n"
"  FILE* muslout = fopen(\"musl.bin\", \"w\");\n"
"  FILE* glibcout = fopen(\"glibc.bin\", \"w\");\n"))

  (define cov-format (string-append
"  musl_snprintf(buf, LEN, \"~a\"~a);\n"
"  fputs(buf, muslout);\n"
"  snprintf(buf, LEN, \"~a\"~a);\n"
"  fputs(buf, glibcout);\n"))

  (define cov-epilogue (string-append
"  fclose(muslout);\n"
"  fclose(glibcout);\n"
"  return 0;\n"
"}\n"))

  (define (cov-make-printf-string c-format c-args)
    (let ([out (open-output-string)])
      (fprintf out cov-format c-format c-args c-format c-args)
      (get-output-string out)))

  (define prologue (string-append
"#include <stdio.h>\n"
"#include <math.h>\n"
"#include <stdint.h>\n"
"#include <wchar.h>\n"
"\n"
"int main(int argc, char* argv[]) {\n"
"  FILE* out = fopen(\"out.bin\", \"w\");\n"))

  (define format (string-append
"  fprintf(out, \"~a\"~a);\n"))

  (define epilogue (string-append
"  fclose(out);\n"
"  return 0;\n"
"}\n"))

  (define (make-printf-string c-format c-args)
    (let ([out (open-output-string)])
      (fprintf out format c-format c-args)
      (get-output-string out)))

  (define (printfs-to-file-string lst)
    (string-append (for/fold ([str prologue])
                     ([printf lst])
                     (string-append str (printf->string printf make-printf-string)))
                   epilogue))

  (define (cov-printfs-to-file-string lst)
    (string-append (for/fold ([str cov-prologue])
                     ([printf lst])
                     (string-append str (printf->string printf cov-make-printf-string)))
                   cov-epilogue))

  (define (printf->string printf converter)
    (define (work args c-format c-args)
      (if (empty? args)
        (converter c-format c-args)
        (let* ([rest (cdr args)]
               [arg (car args)]
               [is-conv (list? arg)]
               [new-c-format (if is-conv
                               (string-append c-format "%" (car arg))
                               (string-append c-format arg))]
               [new-c-args (if (and is-conv
                                    (not (null? (cdr arg))))
                             (string-append c-args ", " (cadr arg))
                             c-args)])
          (work rest new-c-format new-c-args))))
    (work printf "" ""))

)
