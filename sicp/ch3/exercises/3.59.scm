(define (integrate-series s)
  (define (iter s n)
    (cons-stream
     (/ (stream-car s) n)
     (iter (stream-cdr s)
           (+ n 1))))
  (iter s 1))

(define exp-series
  (cons-stream 1 (integrate-series exp-series)))

(define sine-series
  (cons-stream 0 (integrate-series cosine-series)))

(define cosine-series
  (cons-stream 1
               (scale-stream
                (integrate-series sine-series)
                -1)))
