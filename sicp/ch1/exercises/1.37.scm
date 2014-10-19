;; Recursive version
(define (cont-frac n d k)
  (if (= k 1)
      (/ (n k) (d k))
      (/ (n k) (+ (d k) (cont-frac n d (- k 1))))))

;; Iterative version
(define (cont-frac-iter n d k)
  (define (iter i result)
    (if (= i k)
        result
        (iter (+ i 1)
              (/ (n i) (+ (d i) result)))))
  (iter 0 0))

(cont-frac (lambda(i) 1.0)
           (lambda(i) 1.0)
           1000)

(cont-frac-iter (lambda(i) 1.0)
                (lambda(i) 1.0)
                1000)
