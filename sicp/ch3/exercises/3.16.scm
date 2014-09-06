(define (bad-count-pairs x)
  (if (not (pair? x))
      0
      (+ (bad-count-pairs (car x))
         (bad-count-pairs (cdr x))
         1)))

(define z '(a b c))
(bad-count-pairs z)
