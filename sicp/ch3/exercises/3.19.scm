(define (has-loop-quick? x)
  (define (iter l1 l2)
    (cond
     ((or (null? l1) (null? l2)) #f)
     ((not (pair? l1)) #f)
     ((eq? (car l1) (cadr l2)) #t)
     (else
      (iter (cdr l1)
            (cddr l2)))))
  (iter x x))

(define no-loop '(a b c d))
(has-loop-quick? no-loop)

(define cycle '(a b c d))
(set-cdr! (last-pair cycle) cycle)
(has-loop-quick? cycle)
