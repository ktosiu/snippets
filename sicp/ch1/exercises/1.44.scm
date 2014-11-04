(define (compose f g)
  (lambda(x)
    (f (g x))))

(define (repeated f n)
  (define (iter i result)
    (if (= i n)
        result
        (iter (+ i 1) (compose result f))))
  (iter 1 f))

(define dx 0.001)

(define (smooth f)
  (lambda(x)
    (/ (+ (f x) (f (- x dx)) (f (+ x dx)))
       3)))

(define (nth-smooth f n)
  ((repeated smooth n) f))

((nth-smooth sin 5) 1)
(sin 1)
