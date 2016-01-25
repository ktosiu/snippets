;; Recursive
(define (f n)
  (if (< n 3)
      n
      (+ (f (- n 1)) (* (f (- n 2)) 2) (* (f (- n 3)) 3))))

;; Iterative
(define (f1 n)
  (define (iter a b c count)
    (if ( = count 0)
        c
        (iter (+ a (* 2 b) (* 3 c))
              a
              b
              (- count 1))))
  (iter 2 1 0 n))

;; Iterative2
(define (f2 n)
  (define (iter i a b c)
    (if (= i n)
        c
        (iter (+ i 1)
              (+ a (* 2 b) (* 3 c))
              a
              b)))
  (iter 0 2 1 0))

(f1 9)
(f1 3)

(f2 9)

(f 8)
(f 3)
(f 2)
(f 1)
(f 0)
(f -1)

;; Still need to finish the iterative method
