;; Recursive version
(define (cont-frac n d k)
  (define (cont-frac-rec i)
    (if (= i k)
        (/ (n i) (d i))
        (/ (n i)
           (+ (d i) (cont-frac-rec (+ i 1))))))
  (cont-frac-rec 1))

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
