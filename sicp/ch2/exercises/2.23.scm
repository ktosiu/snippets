(define (for-each proc items)
  (if (null? items)
      '()
      (begin (proc (car items))
             (for-each proc (cdr items)))))

(for-each (lambda(x) (newline) (display x))
          (list 1 2 3 5 6))
