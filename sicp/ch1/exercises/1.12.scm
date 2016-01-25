(define (pascal-triangle row col)
  (cond ((> col row) 0)
        ((< col 0) 0)
        ((= col 1) 1)
        (else
         (+ (pascal-triangle (- row 1) (- col 1))
            (pascal-triangle (- row 1) col)))))


(pascal-triangle 5 2)
