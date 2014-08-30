(define (enum-range low high)
  (if (> low high)
      '()
      (cons low (enum-range (+ low 1) high))))

(define (flatmap proc seq)
  (accumulate append '() (map proc seq)))

(define (unique-pairs n)
  (flatmap (lambda (i)
             (map (lambda (j) (list i j))
                  (enum-range 1 (- i 1))))
           (enum-range 1 n)))

(unique-pairs 10)
