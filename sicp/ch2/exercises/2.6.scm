(define zero (lambda(x) (f ((n f) x))))
(define (add-1 n)
  (lambda (f) (lambda (x) (f ((n f) x)))))

(add-1 zero)
