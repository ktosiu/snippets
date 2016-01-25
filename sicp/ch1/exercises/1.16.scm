(define (even? n)
  (= (remainder n 2) 0))

(define (square x)
  (* x x))

(define (exp-iter b n r)
  (cond ((= n 0) r)
        ((even? n) (exp-iter (square b) (/ n 2) r))
        (else (exp-iter b (- n 1) (* b r)))))

(define (exp b n)
  (exp-iter b n 1))

(exp 2 10)
