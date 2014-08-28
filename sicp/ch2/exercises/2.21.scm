(define (square x) (* x x))
(define (square-list items)
  (if (null? items)
      '()
      (cons (square (car items))
            (square-list (cdr items)))))

(define (square-list2 items)
  (map square items))

(display (square-list (list -1 -2 4 6)))
(display (square-list2 (list -1 -2 4 6)))
