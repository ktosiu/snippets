(define (first-deno k)
  (cond ((= k 1) 1)
        ((= k 2) 5)
        ((= k 3) 10)
        ((= k 4) 25)
        ((= k 5) 50)))

(define (cc amount k)
  (cond ((= amount 0) 1)
        ((< amount 0) 0)
        ((= k 0) 0)
        (else (+ (cc amount
                     (- k 1))
                 (cc (- amount (first-deno k)) k)))))

(define (count-change amount) (cc amount 5))

(count-change 10)
