(load "../common/srfi-64-port.scm")
(use-modules (srfi srfi-64))

(define (my-simple-runner filename)
  (let ((runner (test-runner-null))
        (port (open-output-file filename))
        (num-passed 0)
        (num-failed 0))
    (test-runner-on-test-end! runner
      (lambda (runner)
        (case (test-result-kind runner)
          ((pass xpass) (set! num-passed (+ num-passed 1)))
          ((fail xfail) (set! num-failed (+ num-failed 1)))
          (else #t))))
    (test-runner-on-final! runner
       (lambda (runner)
          (format port "Passing tests: ~d.~%Failing tests: ~d.~%"
                  num-passed num-failed)
            (close-output-port port)))
    runner))

(test-runner-factory
 (lambda () (my-simple-runner "/tmp/my-test.log")))
