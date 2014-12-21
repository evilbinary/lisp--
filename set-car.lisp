
(define (my-set-cdr! location value)
     (set! location (cons (car location) value)))

(define x (list 1 2 3))
x
(set-cdr! x x)
x
(set-car! x x)
x

(define a '(1 2 3))
(set-car! a 1000)
a
(set-cdr! a 20)
a



(define a '(1 2 3))
(set-car! a 3)
(set-cdr! a '(4 5 6))
a
(set-car! (car a) 13)
