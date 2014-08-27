(define (gcd x y)
  (if (= y 0)
      x
      (gcd y (remainder x y))))

(define (make-rat n d)
  (let ((g (gcd n d)))
    (cond ((and (< n 0) (< d 0)) (cons (abs (/ n g)) (abs (/ d g))))
          ((and (< n 0) (> d 0)) (cons (/ n g) (/ d g)))
          ((and (>= n 0) (< d 0)) (cons (- 0 (abs (/ n g))) (abs (/ d g))))
          (else (cons (/ n g) (/ d g))))))

(define (numer x) (car x))
(define (denom x) (cdr x))

(define (print-rat x)
  (newline)
  (display (numer x))
  (display "/")
  (display (denom x)))

(define (add-rat x y)
  (make-rat (+ (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))

(define (sub-rat x y)
  (make-rat (- (* (numer x) (denom y))
               (* (numer y) (denom x)))
            (* (denom x) (denom y))))

(define (mul-rat x y)
  (make-rat (* (numer x) (numer y))
            (* (denom x) (denom y))))

(define (div-rat x y)
  (make-rat (* (numer x) (denom y))
            (* (numer y) (denom x))))

(define (equal-rat? x y)
  (= (* (numer x) (denom y))
     (* (numer y) (denom x))))

(define one-half (make-rat -1 -2))
(print-rat one-half)
(define one-third (make-rat 1 -3))
(print-rat one-third)
(print-rat (add-rat one-half one-third))
(print-rat (add-rat one-third one-third))
(print-rat (make-rat 1 -1))
