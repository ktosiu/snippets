(define (half x)
  (/ x 2))

(define (double x)
  (* x 2))

(define (even? x)
  (= (remainder x 2) 0))

(define (fast-mult a b)
  (cond ((= b 0) 0)
        ((= b 1) a)
        ((even? b) (double (fast-mult a (half b))))
        (else (+ a (fast-mult a (- b 1))))))

(fast-mult 500 600)
