(asdf:defsystem #:webapp
  :description "Bobo is Secret Agent."
  :author "Anthony Green <green@spindazzle.org>"
           :version "0"
  :serial t
  :components ((:file "package")
               (:file "irc")
	       (:file "oauth2-google")
	       (:file "tropo")
	       (:file "bobo"))
  :depends-on (:cl-irc
	       :hunchentoot
	       :puri
	       :cl-json
	       :drakma
	       :babel
	       :bordeaux-threads
	       :trivial-timers))
