(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))

(define (cube x) (* x x x))
(define (inc n) (+ n 1))
(define (sum-cube a b)
  (sum cube a inc b))
(sum-cube 1 10)

(define (id x) x)
(define (sum-integers a b)
  (sum id a inc b))
(sum-integers 1 10)

(define (pi-sum a b)
  (sum (lambda(x) (/ 1.0 (* x (+ x 2))))
       a
       (lambda(x) (+ x 4))
       b))
(* (pi-sum 1 1000) 8)

(define (integral f a b dx)
  (define (add-dx x)
    (+ x dx))
  (* dx
     (sum f
          (+ a (/ dx 2.0))
          add-dx
          b)))

(integral cube 0 1 0.01)
(integral sin 0 3.14 0.001)
