;; Recursive version
(define (cont-frac n d k)
  (cont-frac-rec n d k 1))

(define (cont-frac-rec n d k i)
  (if (= i k)
      (/ (n i) (d i))
      (/ (n i)
         (+ (d i) (cont-frac-rec n d k (+ i 1))))))

;; Iterative version
(define (cont-frac-iter n d k)
  (define (iter i result)
    (if (= i 0)
        result
        (iter (- i 1)
              (/ (n i)
                 (+ (d i) result)))))
  (iter k 0))

(cont-frac (lambda (i) 1.0)
           (lambda (i) 1.0)
           100)

(cont-frac-iter (lambda (i) 1.0)
                (lambda (i) 1.0)
                100)
