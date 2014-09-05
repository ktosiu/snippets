(define (make-account init-balance init-password)
  (define password init-password)
  (define balance init-balance)
  (define wrong-tries 0)

  (define (withdraw pass amount)
    (if (eq? pass password)
        (begin (set! wrong-tries 0)
               (if (>= balance amount)
                   (begin (set! balance (- balance amount)) balance)
                   "Insufficient funds"))
        (begin (set! wrong-tries (+ wrong-tries 1))
               (if (>= wrong-tries 7)
                   "call-the-cops"
                   "Incorrect password"))))

  (define (deposit pass amount)
    (if (eq? pass password)
        (begin (set! balance (+ balance amount)) balance)
        (begin (set! wrong-tries (+ wrong-tries 1))
               (if (>= wrong-tries 7)
                   "call-the-cops"
                   "Incorrect password"))))

  (define (dispatch m1 m2)
    (cond ((eq? m2 'withdraw) (lambda (amount) (withdraw m1 amount)))
          ((eq? m2 'deposit) (lambda (amount) (deposit m1 amount)))
          (else
           (error "Unknown message received" m2))))
  dispatch)

(define acc (make-account 100 'password))
((acc 'password 'withdraw) 10)
((acc 'wrong-password 'withdraw) 10)
((acc 'password 'deposit) 1000)
((acc 'wrong-password 'deposit) 1000)
