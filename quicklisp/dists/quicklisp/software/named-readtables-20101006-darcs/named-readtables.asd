;;; -*- Mode:Lisp -*-

(in-package :cl-user)

(defclass asdf::named-readtables-source-file (asdf:cl-source-file) ())

#+sbcl
(defmethod asdf:perform :around ((o asdf:compile-op)
                                 (c asdf::named-readtables-source-file))
  (let ((sb-ext:*derive-function-types* t))
    (call-next-method)))


(asdf:defsystem :named-readtables
  :description "Library that creates a namespace for named readtable akin to the namespace of packages."
  :author "Tobias C. Rittweiler <trittweiler@common-lisp.net>"
  :version "0.9"
  :licence "BSD"
  :default-component-class asdf::named-readtables-source-file
  :components
  ((:file "package")
   (:file "utils"                 :depends-on ("package"))
   (:file "define-api"            :depends-on ("package" "utils"))
   (:file "cruft"                 :depends-on ("package" "utils"))
   (:file "named-readtables"      :depends-on ("package" "utils" "cruft" "define-api"))))

(defmethod asdf:perform ((o asdf:test-op)
                         (c (eql (asdf:find-system :named-readtables))))
  (asdf:operate 'asdf:load-op :named-readtables-test)
  (asdf:operate 'asdf:test-op :named-readtables-test))


(asdf:defsystem :named-readtables-test
  :description "Test suite for the Named-Readtables library."
  :author "Tobias C. Rittweiler <trittweiler@common-lisp.net>"
  :depends-on (:named-readtables)
  :components
  ((:module tests
    :default-component-class asdf::named-readtables-source-file
    :serial t
    :components
    ((:file "package")
     (:file "rt"    :depends-on ("package"))
     (:file "tests" :depends-on ("package" "rt"))))))

(defmethod asdf:perform ((o asdf:test-op)
                         (c (eql (asdf:find-system
                                  :named-readtables-test))))
  (let ((*package* (find-package :named-readtables-test)))
    (funcall (intern (string '#:do-tests) *package*))))

;; (documentation-template:create-template
;;  :named-readtables
;;  :target "/home/tcr/src/contributing/named-readtables/doc/named-readtables.html"
;;  :version (asdf:component-version (asdf:find-system :named-readtables))
;;  :repository "http://common-lisp.net/project/editor-hints/darcs/named-readtables/"
;;  :download-url "http://common-lisp.net/project/editor-hints/releases/named-readtables-0.9.tar.gz")