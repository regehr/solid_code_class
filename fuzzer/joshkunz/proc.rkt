#lang racket

(provide run build rm)

; Run the given binary with the given flags. Returns an immutable hash table
; containing the status code, stdout, stderr, binary name, and list of
; arguments used to invoke the binary. If supplied, the ouput-poirnt given by
; #:input is sent to the spawned processes stdin.
(define (run binary #:input [input-port null] . flags)
 ; Run the program as a subprocess
 (let-values ([(proc proc-stdout proc-stdin proc-stderr)
               (apply subprocess (append (list #f #f #f binary) flags))])
  (when (not (null? input-port))
   (copy-port input-port proc-stdin))
  (close-output-port proc-stdin)
  (let ([proc-output (port->bytes proc-stdout)]
        [proc-error (port->bytes proc-stderr)]
        [exit-code (subprocess-wait proc)])
   (begin0
    (make-immutable-hash `(
     (status . ,exit-code)
     (stdout . ,proc-output)
     (stderr . ,proc-error)
     (binary . ,binary)
     (args   . ,flags)
     )
    )
    (close-input-port proc-stdout)
    (close-input-port proc-stderr)
   )
  )
 )
)

; Writes the output of all given sequences `seqs` to 'to-file'.
(define (build to-file . seqs)
 (let* ([output (open-output-file to-file #:exists 'truncate)]
        [writer (lambda (bytes) (write-bytes bytes output))])
  (sequence-for-each writer (apply in-sequences seqs))
  (close-output-port output)
 )
)

; Deletes the given files if they exist. Fails silently otherwise.
(define (rm . files)
 (when (file-exists? (car files))
  (delete-file (car files)))
 (unless (null? (cdr files)) 
  (rm (cdr files)))
)
