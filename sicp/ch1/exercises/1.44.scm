(define (compose f g)
  (lambda(x)
    (f (g x))))

(define (repeated f n)
  (define (iter i result)
    (if (= i n)
        result
        (iter (+ i 1) (compose result f))))
  (iter 1 f))

(define dx 0.000001)

(define (smooth f)
  (lambda(x)
    (/ (+ (f x) (f (- x dx)) (f (+ x dx)))
       3)))

((smooth sin) 3)
