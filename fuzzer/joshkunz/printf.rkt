#lang racket

(require "random-extra.rkt")
(require "types.rkt")
(require "format.rkt")

(define *printf-arg-range* '(1 5))

(define *printf-prelude* (string->bytes/utf-8
 "#include <stdio.h>
  #include <math.h>
  
  #ifdef MUSL
  #include \"musl.h\"
  #define snprintf musl_snprintf
  #endif

  #define BUFFER_LEN 10000
  char buffer[BUFFER_LEN] = { 0 };

  int main() {\n")
)

(define *printf-epilogue*
 #"    return 0;\n}\n")

(define (gen-args count)
 (if (= count 0) '()
  (let ([type (gen-type)])
   (cons (list (gen-fmt type) type)
         (gen-args (sub1 count)))
  )
 )
)

; Generate a string printf statement with 'spec-count' vars printed.
(define (gen-printf spec-count)
 (let* ([args (gen-args spec-count)]
        [formats (map first args)]
        [values  (map second args)])
  (string-append
   "snprintf(buffer, BUFFER_LEN, \"" 
   (string-join (map fmt->string formats) "")
   "\\n\", "   ; Make sure that all format strings end with '\n' for easier
               ; debugging.
   (string-join (map type-value->string values) ", ")
   "); fputs(buffer, stdout);"
  )
 )
)

; **** Stream Interface ****

(provide printf-stream)

(struct printf-stream
 (count print-prelude?)
 #:methods gen:stream
 [(define (stream-empty? stream)
   (<= (printf-stream-count stream) 0))
  (define (stream-first stream)
   (bytes-append
    (if (printf-stream-print-prelude? stream) *printf-prelude* #"")
    #"    " ; Formatting counts
    (string->bytes/utf-8 
     (gen-printf (apply random-integer *printf-arg-range*)))
    #"\n"
    (if (= (printf-stream-count stream) 1) *printf-epilogue* #"")
   )
  )
  (define (stream-rest stream)
   (printf-stream
    (sub1 (printf-stream-count stream)) #f)
  )]
)
