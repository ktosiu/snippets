(define (unique-triples n)
  (flatmap
   (lambda (i)
     (flatmap
      (lambda (j)
        (map (lambda (k)
               (list i j k))
             (enum-range 1 (- j 1))))
      (enum-range 1 (- i 1))))
   (enum-range 1 n)))

(define (sum seq)
  (accumulate
   +
   0
   seq))

(define (triples-sum-s s n)
  (filter
   (lambda (triple)
     (= (sum triple) s))
   (unique-triples n)))

(triples-sum-s 20 10)
