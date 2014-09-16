(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      #f))

(define (primitive-procedure? proc)
  (tagged-list? proc 'primitive))

(define (procedure-environment p) (cadddr p))

(define (procedure-body p) (caddr p))

(define (procedure-parameters p) (cadr p))

(define (compound-procedure? p)
  (tagged-list? p 'procedure))

(define (false? x)
  (eq? x #f))

(define (true? x)
  (not (eq? x #f)))

(define (cond-clauses exp)
  (cdr exp))

(define (cond-actions clause) (cdr clause))

(define (cond-predicate clause)
  (car clause))

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

(define (first-operand ops)
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
      'false))

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

(define (assignment-variable exp)
  (cadr exp))

(define (assignment-value exp)
  (caddr exp))

(define (text-of-quotation exp)
  (cadr exp))
(define (quoted? exp)
  (tagged-list? exp 'quote))

(define (variable? exp) (symbol? exp))
;(define (self-evaluating?))
(define (make-empty-environment)
 (cons (make-frame '() '()) '()))

(define the-empty-environment '())

(define (make-frame variables values) (cons variables values))

(define (first-frame env)
  (car env))

(define (frame-values frame)
  (cdr frame))

(define (frame-variables frame)
  (car frame))

(define (add-binding-to-frame! var val frame)
  (set-car! frame (cons var (car frame)))
  (set-cdr! frame (cons val (cdr frame))))

(define (extend-environment vars vals base-env)
  (if (= (length vars) (length vals))
      (cons (make-frame vars vals) base-env)
      (if (< (length vars) (length vals))
          (error "Too many arguments supplied" vars vals)
          (error "Too few arguments supplied" vars vals))))

(define (define-variable! var val env)
  (let ((frame (first-frame env)))
    (define (scan vars vals)
      (cond ((null? vars)
             (add-binding-to-frame! var val frame))
            ((eq? var (car vars))
             (set-car! vals val))
            (else (scan (cdr vars) (cdr vals)))))
    (scan (frame-variables frame)
          (frame-values frame))))

(define (set-variable-value! var val env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
             (env-loop (enclosing-environment env)))
            ((eq? var (car vars))
             (set-car! vals val))
            (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
        (error "Unbound variable -- SET!" var)
        (let ((frame (first-frame env)))
          (scan (frame-variables frame)
                (frame-values frame)))))
  (env-loop env))

(define (enclosing-environment env) (cdr env))

(define (lookup-variable-value var env)
  (define (env-loop env)
    (define (scan vars vals)
      (cond ((null? vars)
             (env-loop (enclosing-environment env)))
            ((eq? var (car vars))
             (if (eq? (car vals) '*unassigned*)
                 (error "Unassigned variable" var)
                 (car vals)))
            (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
        (error "Unbound variable" var)
        (let ((frame (first-frame env)))
          (scan (frame-variables frame)
                (frame-values frame)))))
  (env-loop env))

(define (make-procedure parameters body env)
  (list 'procedure parameters body env))

(define (and? exp)
  (tagged-list? exp 'and))
(define (or? exp)
  (tagged-list? exp 'or))

(define (let? exp)
  (tagged-list? exp 'let))

(define (let->combination exp)
  (let ((var-args-pairs (cadr exp))
        (body (cddr exp)))
    (if (null? var-args-pairs)
        (error "Empty let experession")
        (let ((vars (map car var-args-pairs))
              (args (map cadr var-args-pairs)))
          (cons (make-lambda vars body)
                args)))))

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
