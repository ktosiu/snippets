(define (compose f g)
  (lambda(x)
    (f (g x))))

(define (repeated f n)
  (define (iter i result)
    (if (= i n)
        result
        (iter (+ i 1) (compose result f))))
  (iter 1 f))

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

(define (average-damp f)
  (lambda (x) (/ (+ x (f x)) 2)))

;; Experiment
;; n = 2
(define (sqrt x)
  (fixed-point (average-damp (lambda (y) (/ x y)))
               1.0))

(sqrt 2)

;; n =3
(define (cubic-root x)
  (fixed-point (average-damp (lambda (y) (/ x (* y y)))) 1.0))

(define (cubic x) (* x x x))
(cubic (cubic-root 5))

;; n = 4
(define (fourth-root x)
  (fixed-point ((repeated average-damp 2)
                (lambda (y) (/ x (expt y 3))))
               1.0))

(define (fourth x) (expt x 4))
(fourth (fourth-root 9))

;; General n

(define (nth-root n x)
  (fixed-point ((repeated average-damp (/ n 2))
                (lambda (y) (/ x (expt y (- n 1)))))
               1.0))

;; Validate
(fourth-root 90)
(nth-root 8 90)
