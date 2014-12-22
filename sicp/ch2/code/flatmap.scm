(define (accumulate op init seq)
  (if (null? seq)
      init
      (op (car seq)
          (accumulate op init (cdr seq)))))

(define (flatmap proc seq)
  (accumulate append '() (map proc seq)))

(define (enumerate-interval begin end)
  (if (> begin end)
      '()
      (cons begin
            (enumerate-interval (+ begin 1)
                                end))))

(flatmap
 (lambda (i)
   (enumerate-interval 1 (- i 1)))
 (enumerate-interval 1 10))

(define (remove item seq)
  (filter (lambda (x) (not (= x item))) seq))

(define (permutations s)
  (if (null? s)
      (list '())
      (flatmap (lambda (x)
                 (map (lambda (p) (cons x p))
                      (permutations (remove x s))))
               s)))

(permutations (list 1 2 3 4))
