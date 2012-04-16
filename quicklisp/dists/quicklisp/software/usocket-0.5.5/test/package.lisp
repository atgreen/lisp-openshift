;;;; $Id: package.lisp 646 2011-05-01 05:04:23Z ctian $
;;;; $URL: svn://common-lisp.net/project/usocket/svn/usocket/tags/0.5.5/test/package.lisp $

;;;; See the LICENSE file for licensing information.

(in-package :cl-user)

(defpackage :usocket-test
  (:use :common-lisp
	:usocket
	:regression-test)
  (:export #:do-tests
	   #:run-usocket-tests))
