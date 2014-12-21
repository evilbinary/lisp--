;(sys:set-log-level 7)

(define (count-change amount)
  (cc amount 5))

(define i 0)
(define (pi) (begin (display "[") (display i) (display "] ") (set! i (+ i 1) )))
(define (info exp e) (begin (display " ") (display i)(set! i (+ i 1))(display e)  (display exp) (newline) exp))
;(info (+ 1 2 34 34 2  42 34  23 4 23 4 2 1 23 41 2 341 23 41 23 4 ) "====")

(define (cc amount kinds-of-coins)
  (begin  (display "cc (am=") (display  amount ) (display " ko=") (display kinds-of-coins) (display ")")  (newline)
  (cond ((= amount 0) (begin (pi) (display "1<==") (newline) 1) )
        ((or (< amount 0) (= kinds-of-coins 0)) (begin (pi) (display "2<==") (newline) 0 ))
        (else (info  (begin (pi) (display "3<==") (newline)   (+ (cc amount (begin (display "    cc1 (am=") (display amount) (display " ko=") (display (- kinds-of-coins 1)) (display ")") (newline) (- kinds-of-coins 1))) (cc (begin (display "    cc2 (am=") (display (- amount (first-denomination kinds-of-coins))) (display " ko=") (display kinds-of-coins) (display ")") (newline) (- amount (first-denomination kinds-of-coins))) kinds-of-coins)) ) "#3:")) ) ) )

(define (first-denomination kinds-of-coins)
  (begin  (cond ((= kinds-of-coins 1) 1)
        ((= kinds-of-coins 2) 5)
        ((= kinds-of-coins 3) 10)
        ((= kinds-of-coins 4) 25)
        ((= kinds-of-coins 5) 50))))
(count-change 10)
 
