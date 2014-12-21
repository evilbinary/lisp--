(sys:set-log-level 7)

(define count 110)
(define f (lambda () (if (< count 200) (begin (set! count (+ count 1)) (f)) count)))
(f)
