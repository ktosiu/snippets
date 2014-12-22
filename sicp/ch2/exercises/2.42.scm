(define (make-position col row)
  (cons col row))

(define (position-col p)
  (car p))

(define (position-row p)
  (cdr p))

(define (position-equal a b)
  (equal? a b))

(define empty-board '())

(define (adjoin-position col row positions)
  (cons (make-position col row) positions))

(define (queens borad-size)
  (define (queen-cols k)
    (if (= k 0)
        (list empty-board)
        (filter
         (lambda (positions) (safe? k positions))
         (flatmap
          (lambda (rest-of-queens)
            (map (lambda (new-row)
                   (adjoin-position new-row k rest-of-queens))
                 (enumerate-interval 1 borad-size)))
          (queen-cols (- k 1))))))
  (queen-cols borad-size))
