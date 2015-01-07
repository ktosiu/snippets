;; Use the result of 2.69
(define table1 '((E 16) (D 8) (C 4) (B 2) (A 1)))

(define table2 '((J 512) (I 256) (H 128) (G 64) (F 32)
                 (E 16) (D 8) (C 4) (B 2) (A 1)))

(generate-huffman-tree table1)
(generate-huffman-tree table2)
