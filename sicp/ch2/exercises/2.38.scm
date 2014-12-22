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

(fold-left / 1 (list 1 2 3))

(fold-right / 1 (list 1 2 3))

(fold-right list '() (list 1 2 3))

(fold-left list '() (list 1 2 3))
