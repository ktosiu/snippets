(define (fold-right op init seq)
  (if (null? seq)
      init
      (op (car seq)
          (fold-right op init (cdr seq)))))

(define (fold-left op init seq)
  (define (iter result rest)
    (if (null? rest)
        result
        (iter (op result (car rest))
              (cdr rest))))
  (iter init seq))

(display (fold-left / 1 (list 1 2 3)))
(newline)
(display (fold-right / 1 (list 1 2 3)))
(newline)
(display (fold-right list '() (list 1 2 3)))
(newline)
(display (fold-left list '() (list 1 2 3)))
