(define kinds-of-coins 15)
(if (= kinds-of-coins 1)
    1
    (if (= kinds-of-coins 2) 
        5
        (if (= kinds-of-coins 3) 
            10
            (if (= kinds-of-coins 4) 
                25
                (if (= kinds-of-coins 5) 
                    50
                    (begin (display (+ 1 2)) 'else-string))))))

(define (se a)
  (begin (display "eeee=") (display a) (cond ((= a 1) 1)
        ((= a 2) (begin (display 2) 2))
        ((= a 3) (begin (display 3)3))
        ((= a 4) (begin (display 4)4))
        ((= a 5) (begin (display 5)5))
        (else (begin (display 'hhaah ) 1)))))


(define (cc1 a b)
    (if (= a 0) 1
        (if (or (< a 0) (= b 0)) 0
        (+ (cc1 a (- b 1)) (cc1 (- a (se b)) b)))))
(cc1 2 3)



(cc1 4 10)


