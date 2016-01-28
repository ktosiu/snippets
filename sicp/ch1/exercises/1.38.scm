(define (D i)
  (if (= 0 (remainder (+ i 1) 3))
      (* 2.0 (/ (+ i 1) 3))
      1.0))

(cont-frac (lambda(i) 1.0)
           D
           1000)

(cont-frac-iter (lambda (i) 1)
                D
                1000)

(define e
  (+ 2 (cont-frac-iter (lambda (i) 1.0)
                  D
                  1000)))
