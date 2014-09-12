;; Left to Right order evaluation
(define (list-of-values exps env)
  (if (no-operands? exps)
      '()
      (let* ((first (eval (first-operand exps) env))
             (rest (list-of-values (rest-operands exps) env)))
        (cons first rest))))

;; Right to Left evaluation
(define (list-of-values-2 exps env)
  (if (no-operands? exps)
      '()
      (let* ((rest (list-of-values-2 (rest-operands exps) env))
             (first (eval (first-operand exps) env)))
        (cons first rest))))
