;;square
(define (square x)
    (* x x))

(square 21)
(square (+ 2 5))
(square (square 3))

;;sum of squares
(define (sum-of-squares x y)
    (+ (square x) (square y)))

(sum-of-squares 3 4)


(define (f a)
(sum-of-squares (+ a 1) (* a 2)))
(f 5)

;;abs
(define (abs x)
(cond ((< x 0) (- x))
(else x)))

(abs 10)
(abs -10)

(define (abs-1 x)
(if (< x 0)
(- x) x))

(abs 10)

;;>=
(define (>= x y)
(or (> x y) (= x y)))

(display "test >= ")
(>= 1 2)
(>= 2 1)
(>= 2 2)

;;<=
(define (<= x y)
(or (< x y) (= x y)))

(display "test <= ")
(<= 1 234)
(<= 1 1)
(<= 0.2 1.0)

;;sqrt
(define (sqrt-iter guess x)
    (if (good-enough? guess x)
        guess
        (sqrt-iter  (improve guess x) x)))

(define (improve guess x)
    (average guess (/ x guess)))

(define (average x y)
    (/ (+ x y) 2))

(define (good-enough? guess x)
    (< (abs (- (square guess) x)) 0.001))
(define (sqrt x)
    (sqrt-iter 1 x))

(display "sqrt================")
(sqrt 9)
(sqrt (+ 100 37))
;11.704699917758145
(sqrt (+ (sqrt 2) (sqrt 3)))
;1.7739279023207892
(square (sqrt 1000))
;1000.000369924366

;;new-if
(define (new-if predicate then-clause else-clause)
(cond (predicate then-clause)
(else else-clause )))


(new-if (= 2 3) 0 5)
;5
(new-if (= 1 1) 0 5)
;0


;;;a bug please fix it.
(define (sqrt-iter guess x)
(if
(good-enough? guess x) guess
(sqrt-iter (improve guess x) x)))

;(load "lib.lisp")
;(trace 'average)
;(trace 'improve)
;(trace 'sqrt-iter)
;(trace 'good-enough?)
;(trace 'new-if)


(sqrt 9)


;;factorial
(define (factorial n)
(if (= n 1)
1(* n (factorial (- n 1)))))

(factorial 6)

;;fib
(define (fib n)
(cond ((= n 0) 0)
((= n 1) 1)
(else (+ (fib (- n 1))
(fib (- n 2))))))

(fib 6)

;;gcd
(define (gcd a b)
(if (= b 0)
a(gcd b (remainder a b))))

(gcd 206 0)

;;sum
(define (sum term a next b)
(if (> a b)
0(+ (term a)
(sum term (next a) next b))))

(define (inc n) (+ n 1))
(define (sum-cubes a b)
(sum cube a inc b))

(sum-cubes 1 10)
;3025





