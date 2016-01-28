(define (d k)
  (- (* k 2) 1))

(define (tan-cf x k)
  (/ (cont-frac-iter (lambda (i) (- (* x x)))
                 d
                 k)
     (- x)))

(tan-cf 0.5 1000)

(tan 0.5)
