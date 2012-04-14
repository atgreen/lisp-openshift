(asdf:defsystem #:webapp
  :description "This is my webapp template."
  :author "Anthony Green <green@spindazzle.org>"
           :version "0"
  :serial t
  :components ((:file "package")
	       (:file "webapp"))
  :depends-on (:hunchentoot))

