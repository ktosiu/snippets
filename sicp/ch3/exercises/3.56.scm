(define (merge s1 s2)
  (cond ((stream-null? s1) s2)
        ((stream-null? s2) s1)
        (else
         (let ((s1car (stream-car s1))
               (s2car (stream-car s2)))
           (cond ((< s1car s2car)
                  (cons-stream s1car
                               (merge (stream-cdr s1) s2)))
                 ((> s1car s2car)
                  (cons-stream s2car
                               (merge (stream-cdr s2) s1)))
                 (else
                  (cons-stream s1car
                               (merge (stream-cdr s1) (stream-cdr s2)))))))))

(define (scale-stream s n)
  (if (stream-null? s)
      the-empty-stream
      (cons-stream
       (* n (stream-car s))
       (scale-stream (stream-cdr s) n))))

(define s (cons-stream 1
                       (merge (scale-stream s 2)
                              (merge (scale-stream s 3)
                                     (scale-stream s 5)))))

(define (print-stream s n)
  (if (< n 0)
      (newline)
      (begin
        (display (stream-car s))
        (display " ")
        (print-stream (stream-cdr s) (- n 1)))))

(print-stream s 100)
