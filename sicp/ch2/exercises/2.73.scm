(load "../code/math-package.scm")
(use-modules (system vm trace))

(define (variable? x) (symbol? x))
(define (same-variable? v1 v2)
  (and (variable? v1)
       (variable? v2)
       (eq? v1 v2)))

(define (=number? exp num)
  (and (number? exp) (= exp num)))

(define (make-sum a1 a2)
  (cond ((=number? a1 0) a2)
        ((=number? a2 0) a1)
        ((and (number? a1)
              (number? a2)) (+ a1 a2))
        (else
         (list '+ a1 a2))))

(define (make-product m1 m2)
  (cond ((or (=number? m1 0) (=number? m2 0)) 0)
        ((=number? m1 1) m2)
        ((=number? m2 1) m1)
        ((and (number? m1) (number? m2)) (* m1 m2))
        (else
         (list '* m1 m2))))

(define (operator exp) (car exp))
(define (operands exp) (cdr exp))

(define (deriv exp var)
  (cond ((number? exp) 0)
        ((variable? exp)
         (if (same-variable? exp var) 1 0))
        (else ((get 'deriv (operator exp))
               (operands exp)
               var))))

(define (augend ops)
  (if (null? ops)
      (error "Ops is null")
      (car ops)))

(define (addend ops)
  (cond ((> (length ops) 2)
         (cons '+ (cdr ops)))
        ((= (length ops) 2)
         (cadr ops))
        (else
         (error "Invalid number of ops!"))))

(put 'deriv '+
     (lambda (ops var)
       (make-sum (deriv (augend ops) var)
                 (deriv (addend ops) var))))

(define (multiplier ops)
  (if (null? ops)
      (error "Invalid number of ops!")
      (car ops)))

(define (multiplicand ops)
  (cond ((> (length ops) 2)
         (cons '* (cdr ops)))
        ((= (length ops) 2)
         (cadr ops))
        (else
         (error "Invalid number of ops!"))))

(put 'deriv '*
     (lambda (ops var)
       (make-sum
        (make-product (multiplier ops)
                      (deriv (multiplicand ops) var))
        (make-product (deriv (multiplier ops) var)
                      (multiplicand ops)))))

(define (base exp)
  (car exp))

(define (exponent exp)
  (cadr exp))

(define (make-exponentiation base exponent)
  (cond ((=number? exponent 0) 1)
        ((=number? exponent 1) base)
        (else
         (list '** base exponent))))

(put 'deriv '**
     (lambda (ops var)
       (make-product
        (make-product
         (exponent ops)
         (make-exponentiation (base ops)
                              (- (exponent ops) 1)))
        (deriv (base ops) var))))

;; Test Cases
(deriv '(+ x 3) 'x)
(deriv '(* x y) 'x)
(deriv '(* (* x y) (+ x 3)) 'x)
(deriv '(** x 2) 'x)
(deriv '(* x y (+ x 3) (* x y)) 'x)
