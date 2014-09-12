;; Normal implementation
(define (and? exp)
  (tagged-list? exp 'and))

(define (eval-and exp env)
  (define (iter remaining result)
    (cond ((null? remaining) result)
          ((false? result) #f)
          (else (iter (cdr remaining)
                      (eval (car remaining) env)))))
  (iter (cdr exp) #t))

(define (or? exp)
  (tagged-list? exp 'or))

(define (eval-or exp env)
  (define (iter remaining result)
    (cond ((null? remaining) #f)
          ((true? result) #t)
          (else (iter (cdr remaining)
                      (eval (car remaining) env)))))
  (iter (cdr exp) #f))

;; Derived form
;; Todo
;; and->if
;; or->if
