(use-modules (sxml simple))

(define (read-xml file)
  (call-with-input-file file xml->sxml))

(define (write-xml tree file)
  (call-with-output-file
      file
    (lambda (port)
      (sxml->xml tree port))))

(let ((tree (read-xml "example.xml")))
  (write-xml tree "out.xml"))
