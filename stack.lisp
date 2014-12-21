(define stack '())
(define push!
(lambda (x)
(set! stack (cons x stack))))
(define pop!
(lambda ()
(let ((temp (car stack)))
(set! stack (cdr stack))
temp)))
(push! 9)
(push! 8)
(push! 7)
(display stack) (newline)
(display (pop!)) (newline)
(display stack) (newline)


(define make-stack
(lambda ()
(let ((st '()))
(lambda (process arg)
(case process
((push!) (begin
(set! st (cons arg st))
st))
((pop!)  (let ((temp (car st)))
(set! st (cdr st))
temp))
((view)  (display st))
(else "error!"))))))
(define s (make-stack))
(display (s 'push! 9)) (newline)
(display (s 'push! 8)) (newline)
(display (s 'push! 7)) (newline)
(display (s 'pop! 0)) (newline)
(s 'view 0) (newline)