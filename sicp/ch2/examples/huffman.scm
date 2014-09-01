(define (make-leaf sym weight)
  (list 'leaf sym weight))

(define (leaf? object)
  (eq? (car object) 'leaf))

(define (sym-leaf x) (cadr x))

(define (weight-leaf x) (caddr x))

(define (left-branch tree)
  (car tree))

(define (right-branch tree)
  (cadr tree))

(define (syms tree)
  (if (leaf? tree)
      (list (sym-leaf tree))
      (caddr tree)))

(define (weight tree)
  (if (leaf? tree)
      (weight-leaf tree)
      (cadddr tree)))

(define (make-code-tree left right)
  (list left
        right
        (append (syms left) (syms right))
        (+ (weight left) (weight right))))

(define (choose-branch bit branch)
  ((cond ((= bit 0) (left-branch branch))
         ((= bit 1) (right-branch branch))
         (else
          (error "bad bit: " bit)))))

(define (decode bits tree)
  (define (decode-1 bits current-branch)
    (if (null? bits)
        '()
        (let ((next-branch
               (choose-branch (car bits) current-branch)))
          (if (leaf? next-branch)
              (cons (sym-leaf next-branch)
                    (decode-1 (cdr bits) tree))
              (decode-1 (cdr bits) next-branch)))))
  (decode-1 bits tree))

(define (adjoin-set x set)
  (cond ((null? set) (list x))
        ((< (weight x) (weight (car set))) (cons x set))
        (else (cons (car set)
                    (adjoin-set x (cdr set))))))

(define (make-leaf-set pairs)
  (if (null? pairs)
      '()
      (let ((pair (car pairs)))
        (adjoin-set (make-leaf (car pair)
                               (cadr pair))
                    (make-leaf-set (cdr pairs))))))
