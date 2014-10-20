;; Recursive version
(define (cont-frac n d k)
  (define (frac i)
    (if (= i k)
        (/ (n i) (d i))
        (/ (n i) (+ (d i) (frac (+ i 1))))))
  (frac 1))

;; Iterative version
(define (cont-frac-iter n d k)
  (define (iter i result)
    (if (= i 0)
        result
        (iter (- i 1)
              (/ (n i) (+ (d i) result)))))
  (iter k 0))

(cont-frac (lambda(i) 1.0)
           (lambda(i) 1.0)
           1000)

(cont-frac-iter (lambda(i) 1.0)
                (lambda(i) 1.0)
                1000)
