(load "../examples/huffman.scm")

(define (successive-merge pairs-set)
  (if (= 1 (length pairs-set))
      (car pairs-set)
      (successive-merge
       (adjoin-set
        (make-code-tree (car pairs-set) (cadr pairs-set))
        (cddr pairs-set)))))

(define (generate-huffman-tree pairs)
  (successive-merge (make-leaf-set pairs)))

(generate-huffman-tree '((A 4) (B 2) (C 1) (D 1)))
