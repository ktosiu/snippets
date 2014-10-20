(define (d k)
  (- (* k 2) 1))

(define (square x) (* x x))

(define (tan-cf x k)
  (define (tan-cf-recursive i)
    (if (= i k)
        (/ (square x)
           (d i))
        (/ (square x)
           (- (d i) (tan-cf-recursive (+ i 1))))))
  (/ (tan-cf-recursive 1) x))

(tan-cf 0.5 1000)

(tan 0.5)
