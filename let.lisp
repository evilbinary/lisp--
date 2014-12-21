

;let
(define x 'outside)

(let ((x 'inside)
(y x))
(cons x y))
;ret (inside . outside)

(let ((a 3)
(b 4)
(c 5))
(* (+ a b)c))
;ret 35

(define a '())
(set! a 10)
(let ((a 3)
(m a))
(+ m a))
;ret 13

;;let double test

(define my-pi 3.1415)
(let ((my-pi 3) (old-pi my-pi))
(cons my-pi old-pi))
;=> (3 3.1415)


(let ((x 2) (y 3))
(* x y))
;===>  6

(let ((x 2) (y 3))
(let ((x 7)
(z (+ x y)))
(* z x)))
;===>  35


;;let* double test
(define my-pi 3.1415)

(let* ((my-pi 3) (old-pi my-pi))
(list my-pi old-pi))
;=> (3 3)

;let*
(define x 'outside)
(let* ((x 'inside)
(y x))
(list x y))
;;ret (inside inside)


(let ((x 2) )
(let ((y x))
(cons x y)))
;=> (2 . 2)



 (define (a values)
   (let ((f (car values))
         (args (let flat ((args (cdr values)))
                 (if (null? (cdr args))
                     (car args)
                          (cons (car args) (flat (cdr args))) ) )) )
        (begin 
          (display f)
          (display "  =")
          (display args)
           
               
               ))
   )
