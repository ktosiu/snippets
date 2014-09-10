(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #f))

(define (cond-clauses exp)
  (cdr exp))

(define (cond-actions clause) (cdr clause))

(define (cond-predicate clauses)
  (car clauses))

(define (cond-else-clause? clause)
  (eq? (cond-predicate clause) 'else))

(define (cond? exp) (tagged-list? exp 'cond))

(define (expand-clauses clauses)
  (if (null? clauses)
      'false
      (let ((first (car clauses))
            (rest (cdr clauses)))
        (if (cond-else-clause? first)
            (if (null? rest)
                (sequence->exp (cond-actions first))
                (error "Else clause is not last"))
            (make-if (cond-predicate first)
                     (sequence->exp (cond-actions first))
                     (expand-clauses rest))))))

(define (cond->if exp)
  (expand-clauses (cond-clauses exp)))

(define (rest-operands ops)
  (cdr ops))

(define (first-operands ops)
  (car ops))

(define (no-operands? ops)
  (null? ops))

(define (operands exp) (cdr exp))

(define (operator exp) (car exp))

(define (application? exp)
  (pair? exp))

(define (make-begin seq)
  (cons 'begin seq))

(define (sequence->exp seq)
  (cond ((null? seq) seq)
        ((last-exp? seq) (first-exp seq))
        (else (make-begin seq))))

(define (rest-exps exps)
  (cdr exps))

(define (first-exp exps)
  (car exps))

(define (last-exp? exps)
  (null? (cdr exps)))

(define (begin-actions exp) (cdr exp))

(define (begin? exp)
  (tagged-list? exp 'begin))

(define (make-if predicate consequent alternative)
  (list 'if predicate consequent alternative))

(define (if-alternative exp)
  (if (not (null? (cdddr exp)))
      (cadddr exp)
      #f))

(define (if-consequent exp)
  (caddr exp))

(define (if-predicate exp)
  (cadr exp))

(define (if? exp)
  (tagged-list? exp 'if))

(define (make-lambda parameters body)
  (cons 'lambda (cons parameters body)))

(define (lambda-body exp)
  (cddr exp))

(define (lambda-parameters exp)
  (cadr exp))

(define (lambda? exp)
  (tagged-list? exp 'lambda))

(define (definition-value exp)
  (if (symbol? (cadr exp))
      (caddr exp)
      (make-lambda (cdadr exp)
                   (cddr exp))))

(define (definition-variable exp)
  (if (symbol? (cadr exp))
      (cadr exp)
      (caadr exp)))

(define (definition? exp)
  (tagged-list? exp 'define))

(define (assignment? exp)
  (tagged-list? exp 'set!))

(define (text-of-quotation exp)
  (cadr exp))
(define (quoted? exp)
  (tagged-list? exp 'quote))

;(define (variable?))
;(define (self-evaluating?))

(define (eval-definition exp env)
  (define-variable! (definition-variable exp)
                    (eval (definition-value exp) env)
                    env)
  'ok)

(define (eval-assignment exp env)
  (set-variable-value! (assignment-variable exp)
                       (eval (assignment-value exp) env)
                       env)
  'ok)

(define (eval-sequence exps env)
  (cond ((last-exp? exps) (eval (first-exp exps) env))
        (else
         (eval (first-exp exps) env)
         (eval-sequence (rest-exps exps) env))))

(define (eval-if exp env)
  (if (true? (eval (if-predicate exp) env))
      (eval (if-consequent exp) env)
      (eval (if-alternative exp) env)))

(define (list-of-values exps env)
  (if (no-operands? exps)
      '()
      (cons (eval (first-operand exps) env)
            (list-of-values (rest-operands exps) env))))

(define (apply procedure arguments)
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure procedure arguments))
        ((compound-procedure? procedure)
         (eval-sequence
          (procedure-body procedure)
          (extend-environment
           (procedure-parameters procedure)
           arguments
           (procedure-environment procedure))))
        (else
         (error "Unknown procedure type -- APPLY" procedure))))

(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp)
                         (lambda-body exp)
                         env))
        ((begin? exp)
         (eval-sequence (begin-actions exp) env))
        ((cond? exp) (eval (cond->if exp) env))
        ((application? exp)
         (apply (eval (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
         (error "Unknown expression type -- EVAL" exp))))
