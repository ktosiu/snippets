(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

(define (count-leaves t)
  (accumulate
   (lambda (x y)
     (+ (if (pair? x)
            (count-leaves x)
            1)
        y))
   0
   t))

(display (count-leaves (list (list 1 2 (list 1 2) 3) (list 1 (list 3 4) 2 3))))
