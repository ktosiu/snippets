(define (fib n)
  (cond ((< n 2) n)
        (else
         (+ (fib (- n 1))
            (fib (- n 2))))))

(define (fib-iter a b count)
  (if (= count 0)
      b
      (fib-iter (+ a b) a (- count 1))))

(fib-iter 1 0 100)

(define (even? n)
  (= (remainder n 2) 0))

;; use fast doubling method to do this
(define (fast-fib-iter a b p q count)
  (cond ((= count 0) b)
        ((even? count)
         (fast-fib-iter a
                        b
                        (+ (* p p) (* q q))
                        (+ (* 2 p q) (* q q))
                        (/ count 2)))
        (else
         (fast-fib-iter (+ (* b q) (* a q) (* a p))
                        (+ (* b p) (* a q))
                        p
                        q
                        (- count 1)))))

(define (fast-fib n)
  (fast-fib-iter 1 0 0 1 n))

(fast-fib 10000)
