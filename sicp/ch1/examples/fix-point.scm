(define tolerance 0.00001)

(define (fixed-point f first-guest)
  (define (close-enough? v1 v2)
    (< (abs (- v1 v2)) tolerance))
  (define (try guess)
    (let ((next (f guess))
          )
      (if (close-enough? guess next)
          next
          (try next))))
  (try first-guest))

(fixed-point cos 1.0)
(fixed-point (lambda(x) (+ (sin x) (cos x)))
             1.0)

(define (sqrt x)
  (fixed-point (lambda(y) (average y (/ x y)))
               1.0))

(sqrt 6)
