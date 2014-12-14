(define (make-center-percent center percent)
  (cons center percent))

(define (percent interval)
  (cdr interval))

(define (center interval)
  (car interval))
