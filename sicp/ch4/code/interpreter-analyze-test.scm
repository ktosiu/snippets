(load "interpreter-analyze.scm")
(load "interpreter-global-environment.scm")

(eval '(define a 1) the-global-environment)
(eval '(* 3 3) the-global-environment)
