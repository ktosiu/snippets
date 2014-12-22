(equal? '(a b c d)
        '(a b c d))

(equal? '(a b c d)
        '(a (b) c d))
(eq? 'a 'b)
(eq? 'a 'a)

(define (my-equal? a b)
  (if (and (not (null? a))
           (not (null? b)))
      (if (eq? (car a) (car b))
          (my-equal? (cdr a) (cdr b))
          #f)
      (if (and (null? a) (null? b))
          #t
          #f)))

(my-equal? '(a b c d) '(a b c d))
