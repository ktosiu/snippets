(define (plus-abs a b)
  ((if (> b 0) + -) a b))

(plus-abs 5 -8)
