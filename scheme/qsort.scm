(define (qsort lst)
  (if (null? lst) '()
      (append (qsort (filter (lambda (x) (< x (car lst))) lst))
              (list (car lst))
              (qsort (filter (lambda (x) (> x (car lst))) lst)))))

(qsort '(5 3 1 6 7 4 10))
