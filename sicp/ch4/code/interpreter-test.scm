(load "./interpreter.scm")

; 4.1.2
(self-evaluating? 1)
(self-evaluating? 'a)
(self-evaluating? "adf")

(variable? 1)
(variable? 'a)
(variable? "ab")

(quoted? '(quote (a b c)))
(quoted? '(' (a b c)))
(text-of-quotation '(quote (a b c)))
(assignment? '(set! var 1))
(assignment-variable '(set! var 1))
(assignment-value '(set! var 1))

(definition? '(define a 1))
(definition-variable '(define a 1))
(definition-variable '(define (proc a b)))
(definition-value '(define a 1))
(definition-value '(define (proc a b) (yes)))

(lambda? '(lambda (x) (* x x)))
(lambda-parameters '(lambda (x) (* x x)))
(lambda-body '(lambda (x) (* x x)))

(define if-exp
  (make-if 'pred 'then 'else))
(if? if-exp)
(if-predicate if-exp)
(if-consequent if-exp)
(if-alternative if-exp)
(if-alternative '(if pred then))

(define begin-exp (make-begin '((* x x) (+ y y))))
(begin? begin-exp)
(begin-actions begin-exp)
(last-exp? '((* x x) (+ y y)))
(rest-exps '((* x x) (+ y y)))
(first-exp '((* x x) (+ y y)))

(sequence->exp '((set! a 1) (set! a 2)))
(sequence->exp '())
(sequence->exp '((* x x)))

(application? '(a b c d))
(operator '(a b c d))
(operands '(a b c d))
(no-operands? (operands '(a b)))
(first-operand (operands '(a b)))
(rest-operands (operands '(a b)))
(no-operands? (operands '(a)))

(define cond-exp
  '(cond ((< a 0) -1)
         ((> a 0) 1)
         (else 0)))
(cond? cond-exp)
(cond-clauses cond-exp)
(cond->if cond-exp)

the-empty-environment
the-global-environment

primitive-procedures
(primitive-procedure-names)
(primitive-procedure-objects)

(primitive-procedure? (list 'primitive '(cons a b)))
(primitive-implementation (list 'primitive '(cons a b)))
