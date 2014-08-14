(define (square x) (* x x))

(define (average x y)
  (/ (+ x y) 2))

(define (improve guess x)
  (average guess (/ x guess)))

(define (good-enough? x next-guess)
  (< (abs (- x next-guess)) 0.001))

(define (sqrt-iter guess x)
  (define next-guess (improve guess x))
  (if (good-enough? guess next-guess)
      guess
      (sqrt-iter next-guess x)))

(sqrt-iter 1.0 5)
