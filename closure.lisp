(define closure-demo
  (let ((y 5))
    (lambda (x)
      (set! y (+ y x))
      y)))

(closure-demo 1)
(closure-demo 1)
(closure-demo 1)