(define (random-in-range low high)
  (let ((range (- high low)))
    (+ low (random range))))

(define (monte-carlo trials experiment)
  (define (iter trials-remaining trials-passed)
    (cond ((= trials-remaining 0)
           (/ trials-passed trials))
          ((experiment)
           (iter (- trials-remaining 1) (+ trials-passed 1)))
          (else
           (iter (- trials-remaining 1) trials-passed))))
  (iter trials 0))

(define (rect-area x1 x2 y1 y2)
  (abs (* (- x2 x1) (- y2 y1))))

(define (estimate-integral p x1 x2 y1 y2 n-trials)
  (let ((integral-test
          (lambda ()
            (p (random-in-range x1 x2)
               (random-in-range y1 y2)))))
    (*  (rect-area x1 x2 y1 y2)
        (monte-carlo n-trials integral-test))))

(define (square x) (* x x))

(define (unit-pred x y)
  (<=
    (+ (square x) (square y))
    1))

(estimate-integral unit-pred 1.0 -1.0 1.0 -1.0 100000)
