(define (square x) (* x x))
(define (divides? t n)
  (= (remainder t n) 0))

(define (find-divisor n t)
  (cond ((> (square t) n) n)
        ((divides? t n) t)
        (else (find-divisor n (+ t 1)))))

(define (smallest-divisor n) (find-divisor n 2))
(define (prime? n)
  (= n (smallest-divisor n)))
(prime? 3)
(smallest-divisor 199)
