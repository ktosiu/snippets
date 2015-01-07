(load "../code/huffman.scm")

(define sample-tree
  (make-code-tree (make-leaf 'A 4)
                  (make-code-tree
                   (make-leaf 'B 2)
                   (make-code-tree (make-leaf 'D 1)
                                   (make-leaf 'C 1)))))

(define sample-message '(0 1 1 0 0 1 0 1 0 1 1 1 0))

(leaf? sample-tree)
(left-branch sample-tree)
(right-branch sample-tree)
(syms sample-tree)
(weight sample-tree)
(choose-branch 0 sample-tree)
(decode sample-message sample-tree)
