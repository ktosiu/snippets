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

(define (square x) (* x x))

(define (pi n)
  (* 4
     (product (lambda (x)
                (/ (* (* x 2.0) (* 2 (+ x 1))) (square (+ 1 (* 2 x)))))
              1
              (lambda (x) (+ x 1))
              n)))

(pi 100)

(factorial 5)
