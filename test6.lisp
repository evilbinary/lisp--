(load "/Users/evil/dev/lisp/lisp--/lisp--/lib.lisp")
(load "lib.lisp")

;;<=
(define (<= x y)
(or (< x y) (= x y)))

(define loop
  (lambda(x y)
    (if (<= x y)
        (begin (display x) 
               (display " ") 
               (set! x (+ x 1))
               (loop x y)) )))
;(trace 'loop)
;(trace 'if)
(loop 1 10)
(newline)

(define true #t)
(define false #f)

(load "meval.scm")
;(load "/Users/evil/dev/lisp/lisp--/lisp--/meval.scm")

;(load "/Users/evil/dev/lisp/lisp--/lisp--/allcode/ch4-mceval.scm")

;(load "./allcode/ch4-mceval.scm")
;(load "./allcode/ch4-leval.scm")
;(driver-loop)




