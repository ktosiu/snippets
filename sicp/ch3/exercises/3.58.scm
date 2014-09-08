(define (expand num den radix)
  (cons-stream
   (quotient (* num radix) den)
   (expand (remainder (* num radix) den) den radix)))

(define s1 (expand 1 7 10))
(define s2 (expand 3 8 10))
(define s3 (expand 1 3 10))
(print-stream s1 100)
(print-stream s2 100)
(print-stream s3 100)
