 (let ((w (lambda (w)
            (lambda (f)
              (f ((w w) f)) ) )))
   (w w))
