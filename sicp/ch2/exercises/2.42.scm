;; Not solved correctly, need to correct it in the future

(define empty-board '())
(define (make-position row col)
  (cons row col))
(define (position-row pos) (car pos))
(define (position-col pos) (cdr pos))
(define (position-equal a b)
  (equal? a b))
(define (adjoin-position row col positions)
  (append positions (list (make-position row col))))

(define (queens board-size)
  (define (queen-cols k)
    (if (= k 0)
        (list empty-board)
        (filter
         (lambda (positions) (safe? k positions))
         (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enum-range 1 board-size)))
          (queen-cols (- k 1))))))
  (queen-cols board-size))
