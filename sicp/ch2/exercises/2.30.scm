(define (square x) (* x x))
(define (square-tree t)
  (cond ((null? t) '())
        ((not (pair? t)) (square t))
        (else
         (cons (square-tree (car t))
               (square-tree (cdr t))))))

(define (square-tree1 t)
  (map (lambda(sub-tree)
         (if (pair? sub-tree)
             (square-tree1 sub-tree)
             (square sub-tree)))
       t))

(display
 (square-tree1
  (list 1
        (list 2 (list 3 4) 5)
        (list 6 7))))
