(define (dec a) (- a 1))
(define (inc a) (+ a 1))
(define (plus a b)
  (if (= a 0)
      b
      (inc (plus (dec a) b))))
(define (plus1 a b)
  (if (= a 0)
      b
      (plus1 (dec a ) (inc b))))

(plus 8 7)
(plus1 9 8)
