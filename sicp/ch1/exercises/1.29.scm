(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))

(define (simpson-integral f a b n)
  (let ((h (/ (- b a) n)))
    (define (simpson-term k)
      (* (f (+ a (* k h)))
         (cond ((or (= 0 k) (= n k)) 1)
               ((odd? k) 4)
               (else 2))))
    (* (/ h 3.0) (sum simpson-term 0 (lambda(x) (+ x 1)) n))))

(define (cube x) (* x x x))

(simpson-integral cube 0 1 1000)
