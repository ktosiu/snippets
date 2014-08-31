(define (elem-of-multiset? x set)
  (cond ((null? set) #f)
        ((equal? x (car set)) #t)
        (else (elem-of-set? x (cdr set)))))

(define (adjoin-multiset x set)
  (cons x set))

(define (union-multiset set1 set2)
  (append set1 set2))

(define (intersetion-multiset set1 set2)
  (cond ((or (null? set1) (null? set2)) '())
        ((elem-of-set? (car set1) set2)
         (cons (car set1)
               (intersetion-set (cdr set1) set2)))
        (else (intersetion-set (cdr set1) set2))))

(union-multiset '(a b c) '(b c d))
(adjoin-multiset 'a '(a b c d))
(elem-of-multiset? 'a '(a b c))
(intersetion-multiset '(a b c c d) '(b c c d))
