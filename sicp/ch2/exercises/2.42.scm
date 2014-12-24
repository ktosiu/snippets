(define (make-position row col)
  (cons row col))

(define (position-col p)
  (cdr p))

(define (position-row p)
  (car p))

(define (position-equal a b)
  (equal? a b))

(define empty-board '())

(define (adjoin-position row col positions)
  (append positions (list (make-position row col))))

(define (attack? a b)
  (cond ((= (position-col a) (position-col b)) #t)
        ((= (position-row a) (position-row b)) #t)
        ((= (abs (- (position-col a) (position-col b)))
            (abs (- (position-row a) (position-row b)))) #t)
        (else #f)))

(define (safe? k positions)
  (let ((kth-position (list-ref positions (- k 1))))
    (define (iter i pos)
      (if (< i 2)
          #t
          (and (not (attack? kth-position (car pos)))
               (iter (- i 1) (cdr pos)))))
    (iter k positions)))

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

(length (queens 9))
(queens 5)
