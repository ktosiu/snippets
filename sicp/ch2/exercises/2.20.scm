(define (same-parity? a b)
  (or
   (and (even? a) (even? b))
   (and (odd? a) (odd? b))))

(define (same-parity a . b)
  (define (filter l)
    (if (null? l)
        '()
        (let ((c (car l)))
          (if (same-parity? a c)
              (cons c (filter (cdr l)))
              (filter (cdr l))))))
  (cons a (filter b)))

(display (same-parity 1 2 3 4 5 6 7))
(display (same-parity 2 3 4 5 6 7))
