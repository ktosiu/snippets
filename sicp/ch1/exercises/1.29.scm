(define (product term a next b)
  (if (> a b)
      1
      (* (term a)
         (product term (next a) next b))))

(define (product-iter term a next b)
  (define (iter a result)
    (if (> a b)
        result
        (iter (next a)
              (* (term a) result))))
  (iter a 1))

(define (product-integer a b)
  (product-iter (lambda(x) x)
           a
           (lambda(x) (+ x 1))
           b))
(product-integer 1 5)

(define (square x) (* x x))

(define (pi-product a b)
  (product-iter
     (lambda(n) (/ (* 2.0 2 n (+ n 1)) (square (+ (* 2 n) 1))))
     a
     (lambda(x) (+ x 1))
     b))

(* 4 (pi-product 1 10000))
