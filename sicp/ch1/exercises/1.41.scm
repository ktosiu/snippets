(define (double g)
  (lambda(x) (g (g x)) ))

(define (inc x) (+ x 1))

(((double (double double)) inc) 5)
