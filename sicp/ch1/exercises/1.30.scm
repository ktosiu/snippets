(define (sum term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a)
              (+ (term a) result))))
  (iter a 0))

(define (sum-int a b)
  (sum (lambda(x) x)
       a
       (lambda(x) (+ x 1))
       b))

(sum-int 1 100000)
