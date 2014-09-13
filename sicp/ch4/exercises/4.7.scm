(define (let*? exp)
  (tagged-list? exp 'let*))

(define (let*->nested-let exp)
  (let ((let*-body (caddr exp))
        (let*-binds (cadr exp)))
    (define (build-let binds)
      (if (null? binds)
          let*-body
          (list 'let
                (list (car binds))
                (build-let (cdr binds)))))
    (build-let let*-binds)))
