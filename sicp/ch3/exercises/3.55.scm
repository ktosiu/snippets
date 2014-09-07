(define (partial-sums s)
  (cons-stream
   (stream-car s)
   (add-streams
    (stream-cdr s)
    (partial-sums s))))

(define s (partial-sums (integers-starting-from 1)))

(stream-ref s 100)
