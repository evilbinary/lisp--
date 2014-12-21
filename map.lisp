(not 1)

(define (atom? x) (not (pair? x)))

(pair? '(a . b))
;===>  #t
(pair? '(a b c))
;===>  #t
(pair? '())
;===>  #f

;(pair? '#(a b))
;===>  #f

(define (map fn l)
    (if (pair? l)
            (cons (fn (car l)) (map fn (cdr l)))
        '()))
(define (cadr o)
    (car (cdr o)))

;(map + '(1 2 3) '(4 5 6) )
(map cadr '((a b) (d e) (g h)))
(map (lambda (n) (* n n))
'(1 2 3 4 5))

(define (add a b c d e)
    (+ a b c d e))
;(add 1 2 3 4 5)
(define (map proc items)
  (if (null? items)
      nil
      (cons (proc (car items))
            (map proc (cdr items)))))
(load "lib.lisp")
(map abs '( -10 2.5 -11.6 17))


