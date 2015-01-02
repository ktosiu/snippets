(define (elem-of-set? x set)
  (cond ((null? set) #f)
        ((equal? x (car set)) #t)
        (else (elem-of-set? x (cdr set)))))

(define (adjoin-set x set)
  (if (elem-of-set? x set)
      set
      (cons x set)))

(define (intersetion-set set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((elem-of-set? (car set1) set2)
         (cons (car set1)
               (intersetion-set (cdr set1) set2)))
        (else (intersetion-set (cdr set1) set2))))

(define (union-set set1 set2)
  (cond ((null? set1) set2)
        ((null? set2) set1)
        ((elem-of-set? (car set1) set2)
         (union-set (cdr set1) set2))
        (else
         (cons (car set1)
               (union-set (cdr set1) set2)))))

(union-set '(a b e) '(a b c d e))
