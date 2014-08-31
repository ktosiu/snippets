(define (adjoin-set x set)
  (cond ((null? set) (cons x '()))
        ((= x (car set)) set)
        ((< x (car set)) (cons x set))
        (else
         (cons (car set)
               (adjoin-set x (cdr set))))))

(adjoin-set '5 '(1 2 3 4 5))
