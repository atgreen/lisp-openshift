;;;; $Id: spawn-thread.lisp 614 2011-03-30 08:16:10Z ctian $
;;;; $URL: svn://common-lisp.net/project/usocket/svn/usocket/tags/0.6.0.1/vendor/spawn-thread.lisp $

;;;; SPWAN-THREAD from GBBopen's PortableThreads.lisp

(in-package :usocket)

#+(and digitool ccl-5.1)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew ':digitool-mcl *features*))

;;; ---------------------------------------------------------------------------
;;; Add clozure feature to legacy OpenMCL:

#+(and openmcl (not clozure))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew ':clozure *features*))

;;; ===========================================================================
;;;  Features & warnings

#+(or (and clisp (not mt))
      cormanlisp
      (and cmu (not mp)) 
      (and ecl (not threads))
      gcl
      (and sbcl (not sb-thread)))
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew ':threads-not-available *features*))

;;; ---------------------------------------------------------------------------

#+threads-not-available
(defun threads-not-available (operation)
  (warn "Threads are not available in ~a running on ~a; ~s was used."
        (lisp-implementation-type) 
        (machine-type)
        operation))

;;; ===========================================================================
;;;   Spawn-Thread

(defun spawn-thread (name function &rest args)
  #-(or (and cmu mp) cormanlisp (and sbcl sb-thread))
  (declare (dynamic-extent args))
  #+abcl
  (threads:make-thread #'(lambda () (apply function args))
		       :name name)
  #+allegro
  (apply #'mp:process-run-function name function args)
  #+(and clisp mt)
  (mt:make-thread #'(lambda () (apply function args)) 
                  :name name)
  #+clozure
  (apply #'ccl:process-run-function name function args)
  #+(and cmu mp)
  (mp:make-process #'(lambda () (apply function args)) 
                   :name name)
  #+digitool-mcl
  (apply #'ccl:process-run-function name function args)
  #+(and ecl threads)
  (apply #'mp:process-run-function name function args)
  #+lispworks
  (apply #'mp:process-run-function name nil function args)
  #+(and sbcl sb-thread)
  (sb-thread:make-thread #'(lambda () (apply function args))
                         :name name)
  #+scl
  (mp:make-process #'(lambda () (apply function args))
                   :name name)
  #+abcl
  (threads:make-thread #'(lambda () (apply function args))
		       :name name)
  #+threads-not-available
  (declare (ignore name function args))
  #+threads-not-available
  (threads-not-available 'spawn-thread))
