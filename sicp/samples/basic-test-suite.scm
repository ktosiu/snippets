(load "../common/srfi-64-port.scm")
;; Basic test suite
(use-modules (srfi srfi-64))
(test-begin "vec-test")
(define v (make-vector 5 99))
(test-assert (vector? v))
(test-eqv 99 (vector-ref v 2))
(test-end "vec-test")

(test-begin "test-read-eval-string")
(test-equal 7 (test-read-eval-string "(+ 3 4)"))
(test-error (test-read-eval-string "(+ 3))"))
(test-end "test-read-eval-string")
