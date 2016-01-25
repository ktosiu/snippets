(define (filtered-accumulate combiner null-value term a next b predicate?)
  (if (> a b)
      null-value
      (if (predicate? a)
          (combiner (term a)
                    (filtered-accumulate combiner null-value term (next a) next b predicate?))
          (filtered-accumulate combiner null-value term (next a) next b predicate?))))

(define (filtered-accumulate-iter combiner null-value term a next b predicate?)
  (define (iter a result)
    (if (> a b)
        result
        (if (predicate? a)
            (iter (next a)
                  (combiner (term a)
                            result))
            (iter (next a)
                  result))))
  (iter a null-value))

(filtered-accumulate +
                     0
                     (lambda (x) x)
                     1
                     (lambda (x) (+ 1 x))
                     100
                     prime?)

(filtered-accumulate-iter +
                          0
                          (lambda (x) x)
                          1
                          (lambda (x) (+ 1 x))
                          100
                          prime?)
