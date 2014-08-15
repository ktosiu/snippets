(define (square x)
  (* x x))

(define (sum-of-squares x y)
  (+ (square x) (square y)))

(define (sum-of-squares-of-two-larger-numbers a b c)
  (cond ((and (<= a b) (<= a c)) (sum-of-squares b c))
        ((and (<= b a) (<= b c)) (sum-of-squares a c))
        ((and (<= c a) (<= c b)) (sum-of-squares a b))))

(sum-of-squares-of-two-larger-numbers 3 2 1)

(define (sosotln a b c)
  (cond ((and (< a b) (a c)) (sum-of-squares b c))
        (else (sum-of-squares a (max b c)))))

(sosotln 3 2 2)
