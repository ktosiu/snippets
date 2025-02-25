;;; preplib.ss
;;; Copyright (c) 1998 Cadence Research Systems

;;; authors: R. Kent Dybvig and Oscar Waddell


(define-syntax state-case
  (lambda (x)
    (syntax-case x ()
      ((_ (var exp) c1 c2 ...)
       (identifier? (syntax var))
       (syntax (let ((var exp)) (state-case-help var c1 c2 ...)))))))

(define-syntax state-case-help
  (lambda (x)
    (syntax-case x (else)
      ((_ var (else e1 e2 ...))
       (syntax (begin e1 e2 ...)))
      ((_ var ((k ...) e1 e2 ...) c ...)
       (syntax (if (or (state-case-test var k) ...)
                   (begin e1 e2 ...)
                   (state-case-help var c ...)))))))

(define-syntax state-case-test
  (lambda (x)
    (syntax-case x (eof -)
      ((_ var eof)
       (syntax (eof-object? var)))
      ((_ var (char1 - char2))
       (syntax (and (char? var) (char<=? char1 var char2))))
      ((_ var char)
       (syntax (and (char? var) (char=? var char)))))))

(define read-alpha-command
  ; return symbol representing command; assume \ already seen and scan
  ; maximal string of alphabetic chars, e.g., \scheme => symbol scheme
  ; returns || when no command is recognized
  (let ((buf (open-output-string)))
    (lambda (ip)
      (state-case (c (peek-char ip))
        [((#\a - #\z) (#\A - #\Z))
         (let loop ()
           (write-char (read-char ip) buf)
           (state-case (c (peek-char ip))
             [((#\a - #\z) (#\A - #\Z)) (loop)]
             [else (string->symbol (get-output-string buf))]))]
        [else '||]))))

(define read-command
  ; like read-alpha-command, but allows single nonalphabetic char
  ; commands, e.g., \' => |'|
  (let ((buf (open-output-string)))
    (lambda (ip)
      (state-case (c (peek-char ip))
        [((#\a - #\z) (#\A - #\Z))
         (let loop ()
           (write-char (read-char ip) buf)
           (state-case (c (peek-char ip))
             [((#\a - #\z) (#\A - #\Z)) (loop)]
             [else (string->symbol (get-output-string buf))]))]
        [(eof) '||]
        [else (read-char ip) (string->symbol (string c))]))))

(define command-symbol?
  (lambda (cmd) ; true iff command is one character, nonalpabetic
    (let ((s (symbol->string cmd)))
      (and (fx= (string-length s) 1)
           (state-case (c (string-ref s 0))
             [((#\a - #\z) (#\A - #\Z)) #f]
             [else #t])))))

(define read-back-slash
  (lambda (ip)
    (if (eqv? (peek-char ip) #\\)
        (read-char ip)
        (input-error "back slash expected"))))

(define read-open-brace
  (lambda (ip)
    (if (eqv? (peek-char ip) #\{)
        (read-char ip)
        (input-error "open brace expected"))))

(define read-close-brace
  (lambda (ip)
    (if (eqv? (peek-char ip) #\})
        (read-char ip)
        (input-error "close brace expected"))))

(define read-bracketed-text
  (let ((buf (open-output-string)))
    (case-lambda
      [(ip) (read-open-brace ip) (read-bracketed-text ip 1)]
      [(ip depth)
       (state-case (c (read-char ip))
         [(#\}) (if (= depth 1)
                    (get-output-string buf)
                    (begin (write-char #\} buf)
                           (read-bracketed-text ip (- depth 1))))]
         [(#\{) (write-char #\{ buf) (read-bracketed-text ip (+ depth 1))]
         [(eof) (input-error "file ended within bracketed text")]
         [else (write-char c buf) (read-bracketed-text ip depth)])])))

(define read-optional-arg
  (let ((buf (open-output-string)))
    (lambda (ip)
      (state-case (c (peek-char ip))
        [(#\[)
         (read-char ip)
         (let loop ((depth 0))
           (state-case (c (read-char ip))
             [(#\]) (if (= depth 0)
                        (get-output-string buf)
                        (begin (write-char c buf) (loop depth)))]
             [(#\{) (write-char c buf) (loop (+ depth 1))]
             [(#\}) (write-char c buf) (loop (- depth 1))]
             [(eof) (input-error "file ended within optional argument")]
             [else (write-char c buf) (loop depth)]))]
        [else #f]))))

(define push-ifile
  (lambda (ip ifiles)
    (set! current-ifile ip)
    (cons ip ifiles)))

(define pop-ifile
  (lambda (ifiles)
    (let ((ifiles (cdr ifiles)))
      (set! current-ifile (and (not (null? ifiles)) (car ifiles)))
      ifiles)))

(define push-ofile
  (lambda (op ofiles)
    (set! current-ofile op)
    (cons op ofiles)))

(define pop-ofile
  (lambda (ofiles)
    (let ((ofiles (cdr ofiles)))
      (set! current-ofile (and (not (null? ofiles)) (car ofiles)))
      ofiles)))

(define input-error
  (lambda (msg . args)
    (define file-coordinates
      (lambda (ip)
        (let ((n (file-position ip)))
          (file-position ip 0)
          (let f ((n n) (line 1) (char 1) (return? #f))
            (if (= n 0)
                (values line char)
                (state-case (c (read-char ip))
                  [(#\newline) (f (- n 1) (if return? line (+ line 1)) 1 #f)]
                  [(#\return) (f (- n 1) (+ line 1) 1 #t)]
                  [(eof) (values line char)]
                  [else (f (- n 1) line (+ char 1) #f)]))))))
    (let ((ip current-ifile))
      (call-with-values (lambda () (file-coordinates ip))
        (lambda (line char)
          (assertion-violationf #f "~a on line ~d, character ~d of ~s"
            (apply format msg args)
            line char
            (port-name ip)))))))

(define unexpected-command
  (lambda (cmd)
    (input-error "unexpected command '\\~a'" cmd)))

(define math-file-name
  (let ((seq -1))
    (lambda ()
      (set! seq (+ seq 1))
      (format "math/~d" seq))))

(define name->label
  (call-with-values
    (lambda ()
      (let ((s (make-string 256 #\nul)))
        (define fill!
          (lambda (i ls)
            (if (null? ls)
                (values i s)
                (begin
                  (string-set! s (char->integer (car ls)) (integer->char i))
                  (fill! (+ i 1) (cdr ls))))))
        (fill! 0 '(
           #\! #\" #\# #\$ #\% #\& #\' #\( #\) #\* #\+ #\, #\- #\.  #\/ #\:
           #\; #\< #\= #\> #\? #\@ #\[ #\\ #\] #\^ #\_ #\` #\{ #\| #\} #\~
           #\0 #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9
           #\A #\a #\B #\b #\C #\c #\D #\d #\E #\e #\F #\f
           #\G #\g #\H #\h #\I #\i #\J #\j #\K #\k #\L #\l
           #\M #\m #\N #\n #\O #\o #\P #\p #\Q #\q #\R #\r
           #\S #\s #\T #\t #\U #\u #\V #\v #\W #\w #\X #\x
           #\Y #\y #\Z #\z))))
    (lambda (r t)
      (lambda (s)
        (do ((n (string-length s))
             (i 0 (+ i 1))
             (a 0 (+ (* a r)
                     (char->integer
                       (string-ref t
                         (char->integer (string-ref s i)))))))
            ((= i n) (string->symbol (number->string a 36))))))))

(define genlab
  (lambda ()
    (define next-count
      (lambda (fn)
        (cond
          [(assoc fn genlab-counters) =>
           (lambda (a)
             (let ((n (+ (cdr a) 1)))
               (set-cdr! a n)
               n))]
          [else
           (set! genlab-counters
             (cons (cons fn 0) genlab-counters))
           0])))
    (let ((name (file-name-root (port-name current-ifile))))
      (string->symbol
        (format "~a:~a~d" name genlab-prefix (next-count name))))))

(define read-integer ; return integer or #f if none found
  (lambda (ip)
    (string->number
      (list->string
        (let loop ()
          (state-case (c (peek-char ip))
            [((#\0 - #\9)) (read-char ip) (cons c (loop))]
            [else '()]))))))

(define read-def-pattern
  (lambda (ip)
    (let loop ((i 1))
      (state-case (c (peek-char ip))
        [(#\{) '()]
        [(#\#)
         (read-char ip)
         (state-case (c1 (peek-char ip))
           [(#\#) (read-char ip) (list* c1 c (loop i))]
           [else
            (let ((n (read-integer ip)))
              (if (eq? n i)
                  (cons n (loop (+ i 1)))
                  (input-error "invalid \\def argument specifier")))])]
        [(eof) (input-error "unexpected eof after \\def")]
        [else (read-char ip) (cons c (loop i))]))))

(define read-arg
  (lambda (ip cmd)
    (state-case (c (read-char ip))
      [(#\\) (format "\\~a" (read-command ip))]
      [(#\{) (read-bracketed-text ip 1)]
      [(eof) (input-error "unexpected eof reading ~a arguments" cmd)]
      [else (string c)])))

(define read-args
  (lambda (ip pattern cmd)
    (let loop ((pattern pattern))
      (if (null? pattern)
          '()
          (let ((x (car pattern)))
            (cond
              [(integer? x)
               (let ((arg (read-arg ip cmd)))
                 (cons arg (loop (cdr pattern))))]
              [(string? x)
               (let ((arg (read-optional-arg ip)))
                 (cons (or arg x) (loop (cdr pattern))))]
              [(eqv? x #\space)
               (suppress-white-space ip)
               (loop (cdr pattern))]
              [(eqv? (read-char ip) x) (loop (cdr pattern))]
              [else (input-error "~a use does not match pattern" cmd)]))))))

(define expand-template
  (let ((buf (open-output-string)))
    (lambda (template args cmd)
      (let ((sip (open-input-string template)))
        (let loop ()
          (state-case (c (read-char sip))
            [(#\\)
             (write-char c buf)
             (state-case (c (peek-char sip))
               [(#\#) (read-char sip) (write-char c buf)]
               [else (void)])
             (loop)]
            [(#\#)
             (state-case (c (peek-char sip))
               [(#\#) (read-char sip) (write-char #\# buf)]
               [else (let ((n (read-integer sip)))
                       (let ((n (and n (- n 1))))
                         (unless (and n (< n (length args)))
                           (input-error "invalid argument specifier in ~a template" cmd))
                         (display (list-ref args n) buf)))])
             (loop)]
            [(eof) (get-output-string buf)]
            [else (write-char c buf) (loop)]))))))

(define (suppress-white-space ip)
  (state-case (c (peek-char ip))
    [(#\space #\tab #\newline) (read-char ip) (suppress-white-space ip)]
    [else (void)]))

(define parse-index
  (let ((buf (open-output-string)))
   ; if proper-nesting? is true, the characters ", @, !, and | lose their
   ; special meaning within nested groups.
    (lambda (ip proper-nesting?)
      (define nested-group
        (lambda (depth)
          (state-case (c (read-char ip))
            [(#\{)
             (write-char c buf)
             (nested-group (+ depth 1))]
            [(#\})
             (write-char c buf)
             (unless (= depth 0) (nested-group (- depth 1)))]
            [(#\@ #\! #\|)
             (if proper-nesting?
                 (write-char c buf)
                 (input-error "unquoted ~c within nested group in index entry"))
             (nested-group depth)]
            [(#\")
             (if proper-nesting?
                 (write-char c buf)
                 (state-case (c (read-char ip))
                   [(eof) (input-error "file ended within \\index{}")]
                   [else (write-char c buf)]))
             (nested-group depth)]
            [(#\")
             (write-char c buf)
             (unless proper-nesting?
               (state-case (c (peek-char ip))
                 [(#\") (read-char ip) (write-char c buf)]
                 [else (void)]))
             (nested-group depth)]
            [else (write-char c buf) (nested-group depth)])))
      (define before@
        (lambda (ls)
        ; ls is list of levels seen so far
          (state-case (c (read-char ip))
            [(#\})
             (let ((s (get-output-string buf)))
               (values (reverse (cons (cons #f s) ls)) ""))]
            [(#\{)
             (write-char c buf)
             (nested-group 0)
             (before@ ls)]
            [(#\|)
             (let ((s (get-output-string buf)))
               (values (reverse (cons (cons #f s) ls))
                       (read-bracketed-text ip 1)))]
            [(#\@) (after@ ls (get-output-string buf))]
            [(#\!)
             (let ((s (get-output-string buf)))
               (before@ (cons (cons #f s) ls)))]
            [(#\")
             (state-case (c (read-char ip))
               ((eof) (input-error "file ended within \\index{}"))
               (else
                (write-char c buf)
                (before@ ls)))]
            [(#\\)
             (write-char c buf)
             (state-case (c (peek-char ip))
               [(#\") (read-char ip) (write-char c buf)]
               [else (void)])
             (before@ ls)]
            [(eof) (input-error "file ended within \\index{}")]
            [else (write-char c buf) (before@ ls)])))
      (define after@
        (lambda (ls sort-key)
        ; ls is list of levels seen so far
        ; sort-key is sort key part of current level
          (state-case (c (read-char ip))
            [(#\})
             (let ((s (get-output-string buf)))
               (values (reverse (cons (cons sort-key s) ls)) ""))]
            [(#\{)
             (write-char c buf)
             (nested-group 0)
             (after@ ls sort-key)]
            [(#\|)
             (let ((s (get-output-string buf)))
               (values (reverse (cons (cons sort-key s) ls))
                 (read-bracketed-text ip 1)))]
            [(#\@) (input-error "at sign seen after at sign in \\index{}")]
            [(#\!)
             (let ((s (get-output-string buf)))
               (before@ (cons (cons sort-key s) ls)))]
            [(#\")
             (state-case (c (read-char ip))
               ((eof) (input-error "file ended within \\index{}"))
               (else
                ; leave out quote; reinsert later
                (write-char c buf)
                (after@ ls sort-key)))]
            [(#\\)
             (write-char c buf)
             (state-case (c (peek-char ip))
               [(#\") (read-char ip) (write-char c buf)]
               [else (void)])
             (after@ ls sort-key)]
            [(eof) (input-error "file ended within \\index{}")]
            [else (write-char c buf) (after@ ls sort-key)])))
      (before@ '()))))

(define strip-sort-key
  ; presently strips only \scheme{ and matching }
  (let ((buf (open-output-string)))
    (lambda (ip)
      (state-case (c (read-char ip))
        [(#\\)
         (let ((cmd (read-command ip)))
           (case cmd
             [(scheme)
              (read-open-brace ip)
              (display (read-bracketed-text ip 1) buf)
              (strip-sort-key ip)]
             [else (unexpected-command cmd)]))]
        ((eof) (get-output-string buf))
        (else (write-char c buf) (strip-sort-key ip))))))

(define base-macros-file "preplib.stex")

;; support for definitions
(define-syntax global-def
  (syntax-rules ()
    ((_ name expr)
     (set-def! 'name '() #f expr))))

(define set-def!
  (lambda (cmd env conditional? proc)
    (if (null? env)
        (putprop cmd 'def (cons conditional? proc))
        (set-car! env (cons (list* cmd conditional? proc) (car env))))))

(define lookup-env
  ; local to get-def and conditional?
  (lambda (cmd env)
    (cond
      [(null? env) (getprop cmd 'def '(#f . #f))]
      [(assq cmd (car env)) => cdr]
      [else (lookup-env cmd (cdr env))])))

(define get-def
  (lambda (cmd env)
    (cdr (lookup-env cmd env))))

(define conditional?
  (lambda (cmd env)
    (car (lookup-env cmd env))))

;; support for counters
(define get-counter-value
  (lambda (count)
    (getprop count 'counter #f)))

(define set-counter-value!
  (lambda (count value)
    (putprop count 'counter value)))

(define add-subcounter!
  (lambda (counter subcounter)
    (putprop counter 'subcounters
      (cons subcounter (getprop counter 'subcounters '())))))

(define subcounters
  (lambda (counter)
    (getprop counter 'subcounters '())))

(define file-name-root
  (lambda (s)
    (let loop ((i (- (string-length s) 1)))
      (cond
        ((< i 0) s)
        ((char=? (string-ref s i) #\.) (substring s 0 i))
        (else (loop (- i 1)))))))
