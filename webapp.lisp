;;; -*- Mode: LISP; Syntax: COMMON-LISP; Package: WEBAPP; Base: 10 -*-
;;;
;;; Copyright (C) 2012  Anthony Green <green@spindazzle.org>
;;;                         
;;; Webapp is free software; you can redistribute it and/or modify it
;;; under the terms of the GNU General Public License as published by
;;; the Free Software Foundation; either version 3, or (at your
;;; option) any later version.
;;;
;;; Webapp is distributed in the hope that it will be useful, but
;;; WITHOUT ANY WARRANTY; without even the implied warranty of
;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;;; General Public License for more details.
;;;
;;; You should have received a copy of the GNU General Public License
;;; along with Webapp; see the file COPYING3.  If not see
;;; <http://www.gnu.org/licenses/>.

;; Top level for webapp

(in-package :webapp)

(defun start-webapp ()
  (let ((openshift-ip   (sb-ext:posix-getenv "OPENSHIFT_INTERNAL_IP"))
 	(openshift-port (sb-ext:posix-getenv "OPENSHIFT_INTERNAL_PORT")))
    (format t "** Starting hunchentoot @ ~A:~A~%" openshift-ip openshift-port)
    (hunchentoot:start 
     (make-instance 'hunchentoot:easy-acceptor 
 		    :address openshift-ip
 		    :port (parse-integer openshift-port)))
    (loop
	 (sleep 3000))))
