(define (f n)
  (if (< n 3)
      n
      (+ (f (- n 1)) (* (f (- n 2)) 2) (* (f (- n 3)) 3))))

(f 8)
(f 3)
(f 2)
(f 1)
(f 0)
(f -1)

;; Still need to finish the iterative method
