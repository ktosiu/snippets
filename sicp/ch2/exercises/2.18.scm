(define (reverse-iter l)
  (define (iter items result)
    (if (null? items)
        result
        (iter (cdr items)
              (cons (car items) result))))
  (iter l '()))

(define (reverse l)
  (if (null? l)
      '()
      (append
       (reverse (cdr l))
       (list (car l)))))

(display (reverse (list 1 4 9 16 25)))
(reverse (list 1 2 3))
