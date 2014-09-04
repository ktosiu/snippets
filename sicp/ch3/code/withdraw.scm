(define balance 100)

(define (withdraw amount)
  (if (>= balance amount)
      (begin
        (set! balance (- balance amount))
        balance)
      "Insufficient funds"))

(withdraw 10)
(withdraw 50)
(withdraw 50)

(define new-withdraw
  (let ((balance 100))
    (lambda (amount)
      (if (>= balance amount)
          (begin (set! balance (- balance amount))
                 balance)
          "Insufficient funds"))))

(new-withdraw 10)
(new-withdraw 10)
(new-withdraw 90)

(define (make-withdraw balance)
  (lambda (amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount)) balance)
        "Insufficient funds")))

(define w1 (make-withdraw 100))
(define w2 (make-withdraw 100))

(w1 80)
(w2 20)

(define (make-account balance)
  (define (withdraw amount)
    (if (>= balance amount)
        (begin (set! balance (- balance amount)) balance)
        "Insufficient funds"))
  (define (deposit amount)
    (begin
      (set! balance (+ balance amount))
      balance))
  (define (dispatch m)
    (cond ((eq? m 'withdraw) withdraw)
          ((eq? m 'deposit) deposit)
          (else (error "Unknown request" m))))
  dispatch)

(define account (make-account 1000))
((account 'withdraw) 100)
((account 'deposit) 1000)
