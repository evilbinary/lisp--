
(define the-false-value (cons "false" "boolean"))
(define (wrong msg exp) 
  (display msg)
  (display " ")
  (display exp)
  (newline))


(symbol? 'foo)
;===>  #t
(symbol? (car '(a b)))
;===>  #t
(symbol? "bar")
;===>  #f
(symbol? 'nil)
;===>  #t
(symbol? '())
;===>  #f
(symbol? #f)
;===>  #f

(cons 'nil 'nil)
(cons '() 'a )


(null? '())
(null? 5)

(eq? 'nil '())
(eq? '() '())
(display "atom\n")
(define (atom? x) (not (pair? x)))
(atom? 'a)

(define true #t)
(define false #f)

(define (tagged-list? exp tag)
  (if (pair? exp)
      (eq? (car exp) tag)
      false))
;;; New version of evaluate taking care of interpreted booleans

(define the-false-value (cons "false" "boolean"))

(define (evaluate e env)
  (if (atom? e) 
      (cond ((symbol? e) (lookup e env))
            ((or (number? e)(string? e)(char? e)(boolean? e)) ;(vector? e)
             e )
            (else (wrong "Cannot evaluate" e)) )
      (cond 
        ((tagged-list? e 'quote)  (cadr e))
        ((tagged-list? e 'if)     
         (if (not (eq? (evaluate (cadr e) env) the-false-value))
             (evaluate (caddr e) env)
             (evaluate (cadddr e) env) ))
        ((tagged-list? e 'begin)  (eprogn (cdr e) env))
        ((tagged-list? e 'set!)   (update! (cadr e) env (evaluate (caddr e) env)))
        ((tagged-list? e 'lambda) (make-function (cadr e) (cddr e) env))
        (else     (invoke (evaluate (car e) env)
                          (evlis (cdr e) env) )) )
      ) )

(define (eprogn exps env)
  (if (pair? exps)
      (if (pair? (cdr exps))
          (begin (evaluate (car exps) env)
                 (eprogn (cdr exps) env) )
          (evaluate (car exps) env) )
      '() ) )

(define (evlis exps env)
  (if (pair? exps)
      (cons (evaluate (car exps) env)
            (evlis (cdr exps) env) )
      '() ) ) 

(define (lookup id env)
  (if (pair? env)
      (if (eq? (caar env) id)
          (cdar env)
          (lookup id (cdr env)) )
      (wrong "No such binding" id) ) )

(define (update! id env value)
  (if (pair? env)
      (if (eq? (caar env) id)
          (begin (set-cdr! (car env) value)
                 value )
          (update! id (cdr env) value) )
      (wrong "No such binding" id) ) ) 

(define top-env '())

(define (extend env variables values)
  (cond ((pair? variables)
         (if (pair? values)
             (cons (cons (car variables) (car values))
                   (extend env (cdr variables) (cdr values)) )
             (wrong "Too less values") ) )
        ((null? variables)
             (if (null? values)
                 env 
                 (wrong "Too much values") ) )
        ((symbol? variables) (cons (cons variables values) env)) ) ) 

(define (invoke fn args)
  (display fn)
  (if (primitive-procedure? fn)
      ((cadr fn) args)
  (if (compound-procedure? fn) 
      (fn args)
      (wrong "Not a function" fn) ) ) )

(define (add a ) (+ a a a a a a a a a a a))

(define (null-wrap proc)
  (lambda (x y)
    (cond ((not x) #f)
	  ((not y) #f)
	  (else (proc x y)))))

(define primitive-procedures
  (list (list 'car car)
        (list 'cdr cdr)
        (list 'cons cons)
        (list 'null? null?)
	(list '+ +)
	(list '- -)
	(list '/ /)
        (list '* *)
	(list '= (null-wrap =))
	(list 'eq? eq?)
	(list '< (null-wrap <))
	(list '> (null-wrap >))
	(list '>= (null-wrap >=))
	(list '<= (null-wrap <=))
	(list 'display display)
        (list 'apply apply)
        (list 'set-car! set-car!)
        (list 'set-cdr! set-cdr!)
        (list 'map map)
        (list 'list list)
        (list 'length length)
        ;(list 'if if)
        (list 'cond 'cond)
        
        ))

(define (primitive-procedure-names)
  (map car
       primitive-procedures))

(define (primitive-procedure-objects)
  (map (lambda (proc) (list 'primitive (cadr proc)))
       primitive-procedures))
(define (primitive-procedure? proc)
  (tagged-list? proc 'primitive))

(define (compound-procedure? p)
  (tagged-list? p 'procedure))

(define (init)
  (let ((init-env (extend top-env 
                         (primitive-procedure-names)
                         (primitive-procedure-objects))))
    init-env
    ))

;(trace 'extend)
;(trace 'evaluate)
;(evaluate (read ) env.init)
;(add 1000)

  
 (define (start-eval)
  (set! top-env (init))
  (driver-loop))

(define input-prompt ";;; M-Eval input:")
(define output-prompt ";;; M-Eval value:")

(define (driver-loop)
  (prompt-for-input input-prompt)
  (let ((input (read)))
    (let ((output (evaluate input  top-env)))
      (announce-output output-prompt)
      ;(user-print output)
      (display output)
      
      ))
  (driver-loop))

(define (prompt-for-input string)
  (newline) (newline) (display string) (newline))

(define (announce-output string)
  (newline) (display string) (newline))

(define (user-print object)
  (cond ((compound-procedure? object)
	 (display (list 'compound-procedure
			(procedure-parameters object)
			(procedure-body object)
			'<procedure-env>)) )
	;((table? object)
	; (print-table object))
	(else
	 (display object))))

(start-eval)
