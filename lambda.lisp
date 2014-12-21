(define (cons-1 x y)
(lambda (m) (m x y)))
cons-1
(define
(car-1 z)
(z (lambda (p q) p)))
car-1

((lambda x x))