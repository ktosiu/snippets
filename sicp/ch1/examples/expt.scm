(define (exp b n)
  (if (= n 0)
      1
      (* b (exp b (- n 1)))))
(exp 2 10)

(define (exp-iter b counter product)
  (if (= counter 0)
      product
      (exp-iter b (- counter 1) (* b product))))
(define (exp1 b n)
  (exp-iter b n 1))
(exp1 2 10)

(define (square x) (* x x))
(define (even? n) (= (remainder n 2) 0))
(define (fast-exp b n)
  (cond ((= n 0) 1)
        ((even? n) (square (fast-exp b (/ n 2))))
        (else (* b (fast-exp b (- n 1))))))
(fast-exp 2 10000)
