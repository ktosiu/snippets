(define (attach-tag type-tag contents)
  (cons typed-array? contents))

(define (type-tag datum)
  (if (pair? datum)
      (car datum)
      (error "bad tagged datum" datum)))

(define (contents datum)
  (if (pair? datum)
      (cdr datum)
      (error "bad tagged datum" datum)))

(define (rectangular? z)
  (eq? (type-tag z) 'rectangular))

(define (polar? z)
  (eq? (type-tag z) 'polar))

(define (real-part z)
  (car z))

(define (imag-part z)
  (cdr z))

(define (square x) (* x x))

(define (magnitude z)
  (sqrt (+ (square (real-part z)) (square (imag-part z)))))

(define (angle z)
  (atan (imag-part z) (real-part z)))

(define (make-from-real-imag x y)
  (cons x y))

(define (make-from-mag-ang r a)
  (cons (* r (cos a)) (* r (sin a))))

(define (add-complex z1 z2)
  (make-from-real-imag (+ (real-part z1) (real-part z2))
                       (+ (imag-part z1) (imag-part z2))))

(define (sub-complex z1 z2)
  (make-from-real-imag (- (real-part z1) (real-part z2))
                       (- (imag-part z1) (imag-part z2))))

(define (mul-complex z1 z2)
  (make-from-mag-ang (* (magnitude z1) (magnitude z2))
                     (+ (angle z1) (angle z2))))

(define (div-complex z1 z2)
  (make-from-mag-ang (/ (magnitude z1) (magnitude z2))
                     (- (angle z1) (angle z2))))

(define z1 (make-from-real-imag 1 2))
(define z2 (make-from-real-imag 1 1))

(add-complex z1 z2)
(sub-complex z1 z2)
(mul-complex z1 z2)
(div-complex z1 z2)
