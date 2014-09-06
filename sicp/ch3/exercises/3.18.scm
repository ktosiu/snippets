(define (has-loop? x)
  (let ((pairs-table (make-hash-table)))
    (define (traverse-list l)
      (cond ((null? l) #f)
            ((hash-ref pairs-table (car l)) #t)
            (else
             (begin
               (hash-set! pairs-table (car l) 1)
               (traverse-list (cdr l))))))
    (traverse-list x)))

(define no-loop '(a b c d))
(has-loop? no-loop)

(define cycle '(a b c d))
(set-cdr! (last-pair cycle) cycle)
(has-loop? cycle)
