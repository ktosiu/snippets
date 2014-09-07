(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))

(define integers (integers-starting-from 1))
(stream-car integers)
(stream-car (stream-cdr integers))
(stream-ref integers 100)

(define (divisible? x y)
  (= (remainder x y) 0))

(define no-sevens
  (stream-filter (lambda (x) (not (divisible? x 7)))
                 integers))

(stream-ref no-sevens 100)

(define (sieve stream)
  (cons-stream
   (stream-car stream)
   (sieve (stream-filter
           (lambda (x)
             (not (divisible? x (stream-car stream))))
           (stream-cdr stream)))))

(define primes (sieve (integers-starting-from 2)))

(define (get-primes primes n)
  (define (iter i s r)
    (if (>= i n)
        r
        (iter (+ i 1)
              (stream-cdr s)
              (cons (stream-car s) r))))
  (iter 0 primes '()))

(get-primes primes 10)

(define (add-streams s1 s2)
  (stream-map + s1 s2))

(define fibs
  (cons-stream 0
               (cons-stream 1
                            (add-streams (stream-cdr fibs)
                                         fibs))))

(stream-ref fibs 100)
