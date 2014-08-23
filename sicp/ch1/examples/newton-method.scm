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

(define (average x y) (/ (+ x y) 2))

(define (average-damp f)
  (lambda(x) (average x (f x))))

(define (sqrt x)
  (fixed-point (average-damp (lambda(y) (/ x y)))
               1.0))

(define (square x) (* x x))

(define (cube-root x)
  (fixed-point (average-damp (lambda(y) (/ x (square y))))
               1.0))

(sqrt 5)
(cube-root 64)

(define dx 0.00001)

(define (deriv g)
  (lambda(x)
    (/ (- (g (+ x dx)) (g x))
       dx)))

(define (newton-transform g)
  (lambda(x)
    (- x (/ (g x) ((deriv g) x)))))

(define (newton-method g guess)
  (fixed-point (newton-transform g) guess))

(define (sqrt-root x)
  (newton-method (lambda(y) (- (square y) x))
                 1.0))

(sqrt-root 5)
