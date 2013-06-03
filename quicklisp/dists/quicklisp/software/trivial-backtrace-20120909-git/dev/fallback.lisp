(in-package #:trivial-backtrace)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (unless (fboundp 'map-backtrace)
    (defun map-backtrace (func)
      (declare (ignore func))))

  (unless (fboundp 'print-backtrace-to-stream)
    (defun print-backtrace-to-stream (stream)
      (format stream "~&backtrace output unavailable.~%"))))
