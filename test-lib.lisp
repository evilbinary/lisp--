(load "lib.lisp")
(load "/Users/evil/dev/lisp/lisp--/lisp--/lib.lisp")
(define (f x)
    (if (zero? x) 0 (add1 (f (sub1 x)))))


;(trace trace)
;(trace display)

;(sys:set-log-level 7);for debug log

(f 100 )


(define loop
  (lambda(x y)
    (if (<= x y)
        (begin (display x) 
               (display " ") 
               (set! x (+ x 1))
               (loop x y)) )))
(trace loop)
;(trace 'if)

(loop 1 10)

(+ a 1)



(define t  display)

(define (a x) (list x))
display

(sys:update 'display a (sys:top-env))
(display "aaa")
(t "ttttt")

(define (factorial n)
 (define (iter product counter)
     (if (> counter n)
       product
       (iter (* counter product)
        (+ counter 1))))
 (iter 1 1))

(trace factorial)
(factorial 30.1)

