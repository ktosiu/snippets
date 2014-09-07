(define (stream-null? s)
  (null? s))

(define the-empty-stream '())

(define-syntax cons-stream
  (syntax-rules ()
    ((_ x y) (cons x (delay y)))))

(define (stream-car s)
  (car s))

(define (stream-cdr s)
  (force (cdr s)))

(define (stream-ref s n)
  (if (= n 0)
      (stream-car s)
      (stream-ref (stream-cdr s)
                  (- n 1))))

(define (stream-map proc s)
  (if (stream-null? s)
      the-empty-stream
      (cons-stream (proc (stream-car s))
                   (stream-map proc (stream-cdr s)))))

(define (stream-for-each proc s)
  (if (stream-null? s)
      'done
      (begin
        (proc (stream-car s))
        (stream-for-each proc (stream-cdr s)))))

(define (stream-enumerate-interval low high)
  (if (> low high)
      the-empty-stream
      (cons-stream
       low
       (stream-enumerate-interval (+ low 1) high))))

(define (stream-filter pred s)
  (if (stream-null? s)
      the-empty-stream
      (if (pred (stream-car s))
          (cons-stream (stream-car s) (stream-filter pred (stream-cdr s)))
          (stream-filter pred (stream-cdr s)))))

(stream-car
 (stream-cdr
  (stream-filter (lambda (x) (= 0 (remainder x 3)))
                 (stream-enumerate-interval 1 100000000000000))))

;; Delay test
;(define (show x)
;  (display x)
;  x)

;(define ss (cons-stream 1 (show (+ 2 1))))
;(stream-cdr ss)
;; End delay test
