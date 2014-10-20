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

(define (D i)
  (if (= 0 (remainder (+ i 1) 3))
      (* 2.0 (/ (+ i 1) 3))
      1.0))

(cont-frac (lambda(i) 1.0)
           D
           100)

(define e
  (+ 2 (cont-frac-iter (lambda (i) 1.0)
                       D
                       1000)))
