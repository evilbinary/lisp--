

(define (fib n)
(cond ((= n 0) 0)
((= n 1) 1)
(else (+ (fib (- n 1))
(fib (- n 2))))))


;(display ())
;(display "\n")


(define (find-proc name)
    (sys:find name (sys:top-env)))
(define (update-proc name proc)
    (sys:update name proc (sys:top-env)))


;(display "sys:find:")
;(find-proc 'fib)

(define (sub a)
    (- a))
;(update-proc 'fib sub)


(define (print-level indent char)
    (if (< indent 1) (display "")
        (begin (display char) (print-level (- indent 1) char))))

;(print-level 10 "--")


(define *trace-functions nil)
(define *trace-level* 1)
(define (trace name)
    (let ((proc (find-proc name))
           (new-proc nil )
            (result nil)
             )
        (set! new-proc (lambda x
                        (begin (print-level *trace-level* "-") (display name) (display x) (display "\n")
                                (set! *trace-level* (+ *trace-level* 1))
(set! result (proc (car x) (car (cdr x)) ))
;                                (set! result (cons proc  x ))
                                 (set! *trace-level* (- *trace-level* 1)) (print-level *trace-level* "-") (display result) (display "\n") result)) )
        ;(display (cons proc new-proc))
        (update-proc name new-proc)
))

(define (add1 n)
    (+ n 1))
(define (sub1 n)
    (- n 1))
(define (zero? n)
    (= 0 n))

(define (f x)
    (begin
            (if (zero? x) 0 (add1 (f (sub1 x))))) )

;(display (sys:top-env))
;(trace 'f)
(f 10)
;(display (sys:top-env))



;(trace "fib")
(trace 'fib)
;(display (sys:top-env))

;(trace '+)
;(display '-)

;(set! + -)
;(+ 1 2)

;(fib 10)

(define (factorial n)
(if (= n 1)
1(* n (factorial (- n 1)))))

(trace 'factorial)
(factorial 10)


(define suma
(lambda (n)
(if (= n 1)
1
(+ n (suma (- n 1))))))

;(trace 'suma)
;(suma 818)
(suma 1001)


(define (ff i)
    (if (= i 1) i
        (ff (- i 1)) ) )

(trace 'ff)

(ff 10)

(define (f x) (if (zero? x) 0 (add1 (f (sub1 x)))))
(trace 'f)
(f 100)
