(define (make-monitored f)
  (let ((counter 0))
    (lambda (msg)
      (cond ((eq? msg 'how-many-calls?) counter)
            ((eq? msg 'reset-count) (set! counter 0))
            (else
             (begin (set! counter (+ counter 1))
                    (f msg)))))))

(define s (make-monitored sqrt))
(s 100)
(s 'how-many-calls?)
(s 'reset-count)
