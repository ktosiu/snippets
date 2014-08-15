(define (half x)
  (/ x 2))

(define (double x)
  (* x 2))

(define (even? x)
  (= (remainder x 2) 0))

(define (fast-mult-iter a b r)
  (cond ((= b 0) r)
        ((even? b) (fast-mult-iter (double a) (half b) r))
        (else (fast-mult-iter a (- b 1) (+ a r)))))

(fast-mult-iter 500 600 0)
