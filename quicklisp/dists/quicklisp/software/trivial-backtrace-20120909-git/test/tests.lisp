(in-package #:trivial-backtrace-test)

(deftestsuite generates-backtrace (trivial-backtrace-test)
  ())

(addtest (generates-backtrace)
  test-1
  (let ((output nil))
    (handler-case 
	(let ((x 1))
	  (let ((y (- x (expt 1024 0))))
	    (/ 2 y)))
      (error (c)
	(setf output (print-backtrace c :output nil))))
    (ensure (stringp output))
    (ensure (plusp (length output)))))
