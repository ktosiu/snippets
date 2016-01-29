(define (iterative-improve good-enough improve)
  (define (iter x)
    (if (good-enough x)
        x
        (iter (improve x))))
  iter)

(define (sqrt x)
  ((iterative-improve (lambda (y) (< (abs (- x (* y y))) 0.0001))
                      (average-damp (lambda (y) (/ x y))))
   1.0))

(sqrt 2)

;; General version of fixed-point process
(define (fixed-point f)
  ((iterative-improve (lambda (y) (< (abs (- y (f y))) 0.0001))
                      (lambda (y) (f y)))
   1.0))

(fixed-point (lambda (x) (+ 1 (/ 1 x))))
