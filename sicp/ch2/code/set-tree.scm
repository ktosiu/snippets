(define (entry tree) (car tree))
(define (left-branch tree) (cadr tree))
(define (right-branch tree) (caddr tree))
(define (make-tree entry left right)
  (list entry left right))

(define (elem-of-set? x set)
  (cond ((null? set) #f)
        ((= x (entry set)) #t)
        ((< x (entry set))
         (elem-of-set? x (left-branch set)))
        (else
         (elem-of-set? x (right-branch set)))))

(define (adjoin-set x set)
  (cond ((null? set) (make-tree x '() '()))
        ((= x (entry set)) set)
        ((< x (entry set))
         (make-tree (entry set)
                    (adjoin-set x (left-branch set))
                    (right-branch set)))
        (else
         (make-tree (entry set)
                    (left-branch set)
                    (adjoin-set x (right-branch set))))))

(define test-set '())
(adjoin-set 3 (adjoin-set 2 (adjoin-set 1 test-set)))

(define s (make-tree '2
                     (make-tree '1 '() '())
                     (make-tree '3 '() '())))

(elem-of-set? 3 s)
(elem-of-set? 2 s)
(elem-of-set? 1 s)
(elem-of-set? 5 s)
