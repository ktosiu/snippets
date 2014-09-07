(define (stream-map proc . argstreams)
  (if (stream-null? (car argstreams))
      the-empty-stream
      (cons-stream
        (apply proc (map stream-car argstreams))
        (apply stream-map
               (cons proc (map stream-cdr argstreams))))))

(define s1 (stream-enumerate-interval 10 100))
(define s2 (stream-enumerate-interval 20 200))
(define s3 (stream-enumerate-interval 30 300))
(define s (stream-map + s1 s2 s3))
(stream-ref s 2)
