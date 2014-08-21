(define (cont-frac n d k)
  (if (= k 1)
      (/ (n k) (d k))
      (/ (n k) (+ (d k) (cont-frac n d (- k 1))))))

(define (cont-frac-iter n d k)
  (define (iter k result)
    (if (= k 1)
        result
        (iter (- k 1)
              (/ (n k) (+ (d k) result)))))
  (iter k 0))

(cont-frac (lambda(i) 1.0)
           (lambda(i) 1.0)
           1000)

(cont-frac-iter (lambda(i) 1.0)
                (lambda(i) 1.0)
                10000)
