(define (tan-cf x k)
  (define (tan-iter i result)
    (if (= i k)
        0
        (/ (* x x)
           (- (- (* 2 i) 1) (tan-step (+ i 1)))))))
