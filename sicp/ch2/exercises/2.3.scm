(define (make-rect w h)
  (cons w h))

(define (width rect)
  (car rect))

(define (height rect)
  (cdr rect))

(define (area rect)
  (* (width rect)
     (height rect)))

(define (perimeter rect)
  (+ (* 2 (width rect))
     (* 2 (height rect))))

(define (make-rect a b c d)
  (cons (make-segement a b)
        (make-segement a c)))
