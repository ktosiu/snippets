(define (fringe t)
  (cond ((null? t) '())
        ((not (pair? t)) (list t))
        (else (append (fringe (car t))
                    (fringe (cdr t))))))

(define x (list (list 1 2) (list 3 4)))
(display (fringe x))
(display (fringe (list x x)))
