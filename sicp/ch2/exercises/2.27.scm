(define (deep-reverse l)
  (cond ((null? l) '())
        ((not (pair? l)) l)
        (else (append (deep-reverse (cdr l))
                      (list (deep-reverse (car l)))))))

(define x (list (list 1 2) (list 3 4)))
(display (deep-reverse x))
(display (deep-reverse (list x x)))
