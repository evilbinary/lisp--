;#lang racket
;(require racket/trace)	

(define (A k x1 x2 x3)
  (define (B) 
    (set! k (- k 1))
    (A k B x1 x2  ))
  (if (< k 0)
      (+ (x2) (x3))
      (B)))

;(sys:set-log-level 7)
;(trace A)
(A 5 (lambda () 1) (lambda () 2) (lambda () 3))



