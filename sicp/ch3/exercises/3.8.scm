(define f
  (let ((state 1))
    (lambda (n)
      (set! state (* state n))
      state)))

;(+ (f 0) (f 1))
(+ (f 1) (f 0))
