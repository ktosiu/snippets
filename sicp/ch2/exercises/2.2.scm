(define (make-point x y)
  (cons x y))

(define (x-point p)
  (car p))

(define (y-point p)
  (cdr p))

(define (make-segement x y)
  (cons x y))

(define (start-segement s)
  (car s))

(define (end-segement s)
  (cdr s))

(define (average x y)
  (/ (+ x y) 2))

(define (midpoint-segment s)
  (make-point (average (x-point (start-segement s)) (x-point (end-segement s)))
              (average (y-point (start-segement s)) (y-point (end-segement s)))))

(define (print-point p)
  (newline)
  (display "<")
  (display (x-point p))
  (display ",")
  (display (y-point p))
  (display ">"))

(print-point (make-point 1.0 3))
(define test-seg (make-segement (make-point 1.0 3.0) (make-point 2 4)))
(print-point (midpoint-segment test-seg))
