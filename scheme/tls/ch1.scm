'atom
'turky
'1492
'u
'*abc$
'(atom)
'(atom turkey or)
'((atom turky) or)
(car '(a b c))
(car '((a b c) x y z))
(cdr '(hamburger))
(cdr (cdr '((b) (x y) ((c)))))
(cons 'a 'b)
(cons 'a (car '((b) c d)))
(null? 'adf)
(atom? 'harry)
(atom? '(harry had a heap of apples))
(eq? 'harry 'harry)
(eq? '() '())
;(eq? 'milk (cdr (soured milk)))
(define lat?
  (lambda (l)
    (cond
     ((null? l) #t)
     ((atom? (car l)) (lat? (cdr l)))
     (else #f))))

(lat? '(Jack Sprat could eat no chiken fat))
(lat? '((Jack) Sprat could eat no chiken fat))
(lat? '(Jack (Sprat could) eat no chiken fat))
(lat? '())

(define member?
  (lambda (a lat)
    (cond
     ((null? lat) #f)
     (else
      (or (eq? (car lat) a)
          (member? a (cdr lat)))))))

(member? 'meat
         '(mashed potatoes and meat gravy))
(member? 'a '(a b))

(define remember
  (lambda (a lat)
    (cond ((null? lat) '())
          ((eq? a (car lat)) (cdr lat))
          (else
           (cons (car lat) (remember a (cdr lat)))))))

(remember 'mint '(lamb chops and mint jelly))
(remember 'mint '(lamb chops and mint flavored mint jelly))
(remember 'toast '(bacon lettuce and tomato))
(remember 'cup '(coffee cup tea cup and hick cup))
