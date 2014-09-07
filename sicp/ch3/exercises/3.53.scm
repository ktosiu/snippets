(define s (cons-stream 1 (add-streams s s)))
(stream-ref s 10)
