(define (consl x y)
  (lambda(m) (m x y)))

(define (carl z)
  (z (lambda(p q) p)))

(define (cdrl z)
  (z (lambda(p q) q)))

(carl (consl 1 2))
(cdrl (consl 1 2))
