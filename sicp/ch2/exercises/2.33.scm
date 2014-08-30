(define (accumulate op initial sequence)
  (if (null? sequence)
      initial
      (op (car sequence)
          (accumulate op initial (cdr sequence)))))

(define (my-map p sequence)
  (accumulate (lambda (x y) (cons (p x) y)) '() sequence))

(define (my-append seq1 seq2)
  (accumulate cons seq2 seq1))

(define (len seq)
  (accumulate (lambda (x y)
               (+ 1 y) )
              0
              seq))

(display (accumulate + 0 (list 1 2 3 4)))
(newline)
(display (my-map abs (list -1 -2 -3)))
(newline)
(display (my-append (list 1 2 3) (list 4 5 6)))
(newline)
(display (len (list 1 2 3 4 5 6 7 8 9)))
