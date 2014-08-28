(define (my-map proc items)
  (if (null? items)
      '()
      (cons (proc (car items))
            (my-map proc (cdr items)))))

(define (map-reverse proc items)
  (define (iter l result)
    (if (null? l)
        result
        (iter (cdr l)
              (cons (proc (car l)) result))))
  (iter items '()))

(display (my-map abs (list -1 -2 -3 -5)))
(display (map-reverse abs (list -1 -2 -3 -4 -5)))
