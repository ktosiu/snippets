(define (square x) (* x x))

(define (improve x y)
  (/ (+ (/ x (square y)) (* 2 y)) 3))

(define (good-enough? current-guess next-guess)
  (< (abs (- current-guess next-guess)) 0.001))

(define (cube-iter guess x)
  (define next-guess (improve x guess))
  (if (good-enough? guess next-guess)
      guess
      (cube-iter next-guess x)))

(cube-iter 1.0 8)
