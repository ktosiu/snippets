(define (product term a next b)
  (if (> a b)
      1
      (* (term a)
         (product term (next a) next b))))

(define (factorial n)
  (product (lambda (x) x)
           1
           (lambda (x) (+ x 1))
           n))
(define (product term a next b)
  (define (iter i result)
    (if (> i b)
        result
        (iter (next i)
              (* (term i) result))))
  (iter a 1))

(factorial 5)
