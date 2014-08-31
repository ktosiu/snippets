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
  (define (remove predicate set)
    (if (null? set)
        '()
        (if (predicate (car set))
            (remove predicate (cdr set))
            (cons (car set) (remove predicate (cdr set))))))
  (append set1
          (remove (lambda (x) (elem-of-set? x set1))
                  set2)))

(union-set '(a b e) '(a b c d e))
