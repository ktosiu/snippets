(load "interpreter.scm")
(define init-environment (make-empty-environment))
(define-variable! 'a '*unassigned* init-environment)
;(lookup-variable-value 'a init-environment) Should raise an error!
