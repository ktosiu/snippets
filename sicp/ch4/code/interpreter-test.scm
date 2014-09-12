(load "./interpreter.scm")
(load "../../common/srfi-64-port.scm")
(use-modules (srfi srfi-64))
(test-begin "interpreter-test")

; 4.1.1
(define the-env (cons (make-frame '() '()) '()))
(eval '(define a 1) the-env)
(eval 'a the-env)

(apply (make-procedure '(a b) '(a) the-env) '(2 1))

(list-of-values '(a) the-env)
(eval-if '(if #t 1 2) the-env)
(eval-sequence '((define b 2)
                 (define c 3))
               the-env)
(eval-assignment '(set! a 11) the-env)
(eval-definition '(define a 1) the-env)

; 4.1.2
(test-assert (self-evaluating? 1))
(test-assert (self-evaluating? 'a))
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

; 4.1.3
(true? '())
(true? #f)
(false? '())
(false? #f)

(define procedure-exp
  (make-procedure '(a b)
                  '(+ a b)
                  the-empty-environment))

(compound-procedure? procedure-exp)
(procedure-parameters procedure-exp)
(procedure-body procedure-exp)
(procedure-environment procedure-exp)

(define test-env
  (extend-environment
   '(v1 v2 v3 v4)
   '(1 2 3 4)
   the-empty-environment))

(lookup-variable-value 'v1 test-env)
(define-variable! 'v5 5 test-env)
(set-variable-value! 'v1 11 test-env)
(enclosing-environment test-env)
(first-frame test-env)

(define test-frame (make-frame '(v1 v2 v3) '(1 2 3)))
(frame-variables test-frame)
(frame-values test-frame)
(add-binding-to-frame! 'v4 4 test-frame)

; 4.1.4
primitive-procedures
(primitive-procedure-names)
(primitive-procedure-objects)

(primitive-procedure? (list 'primitive '(cons a b)))
(primitive-implementation (list 'primitive '(cons a b)))

(test-end "interpreter-test")
