;;; -*- Mode: LISP; Syntax: COMMON-LISP; Package: DOCUMENTATION-TEMPLATE; Base: 10 -*-
;;; $Header: /usr/local/cvsrep/documentation-template/output.lisp,v 1.17 2010/08/05 19:24:27 edi Exp $

;;; Copyright (c) 2006-2010, Dr. Edmund Weitz.  All rights reserved.

;;; Redistribution and use in source and binary forms, with or without
;;; modification, are permitted provided that the following conditions
;;; are met:

;;;   * Redistributions of source code must retain the above copyright
;;;     notice, this list of conditions and the following disclaimer.

;;;   * Redistributions in binary form must reproduce the above
;;;     copyright notice, this list of conditions and the following
;;;     disclaimer in the documentation and/or other materials
;;;     provided with the distribution.

;;; THIS SOFTWARE IS PROVIDED BY THE AUTHOR 'AS IS' AND ANY EXPRESSED
;;; OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
;;; WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;;; ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
;;; DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
;;; DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
;;; GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;;; INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;;; WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
;;; NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
;;; SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

(in-package :documentation-template)

(defun write-entry-header (name type &key (write-name-p t))
  "Writes the header for a documentation entry of name NAME and
type TYPE.  The HTML anchor will only get a 'name' attribute if
WRITE-NAME-P is true and NAME is not a SETF name."
  (format t "~%~%<!-- Entry for ~A -->~%~%<p><br>[~A]<br><a class=none~@[ name='~A'~]>" 
          name type (and write-name-p (atom name) (string-downcase name))))

(defun write-entry-footer (name doc-string)
  "Writes the footer for a documentation entry for the name NAME
including the documentation string DOC-STRING."
  (format t "~%<blockquote><br>~%~%~@[~A~]~%~%</blockquote>~%~%<!-- End of entry for ~A -->~%"
          (and doc-string (escape-string-iso-8859 doc-string)) name))

(defun write-constant-entry (symbol doc-string)
  "Writes a full documentation entry for the constant SYMBOL."
  (write-entry-header symbol "Constant")
  (format t "<b>~A</b></a>" (string-downcase symbol))
  (write-entry-footer symbol doc-string))

(defun write-special-var-entry (symbol doc-string)
  "Writes a full documentation entry for the special variable
SYMBOL."
  (write-entry-header symbol "Special variable")
  (format t "<b>~A</b></a>" (string-downcase symbol))
  (write-entry-footer symbol doc-string))

(defun write-class-entry (symbol doc-string)
  "Writes a full documentation entry for the class SYMBOL."
  (write-entry-header symbol (if (subtypep symbol 'condition)
                               "Condition type" "Standard class"))
                               
  (format t "<b>~A</b></a>" (string-downcase symbol))
  (write-entry-footer symbol doc-string))

(defun write-lambda-list* (lambda-list &optional specializers)
  "The function which does all the work for WRITE-LAMBDA-LIST and
calls itself recursive if needed."
  (let (body-seen after-required-args-p (firstp t))
    (dolist (part lambda-list)
      (cond (body-seen (setq body-seen nil))
            (t (when (and (consp part) after-required-args-p)
                 (setq part (first part)))
               (unless firstp
                 (write-char #\Space))
               (setq firstp nil)
               (cond ((consp part)
                      ;; a destructuring lambda list - recurse
                      (write-char #\()
                      (write-lambda-list* part)
                      (write-char #\)))
                     ((member part '(&key &optional &rest &allow-other-keys &aux &environment &whole))
                      ;; marks these between <tt> and </tt>
                      (setq after-required-args-p t)
                      (format t "<tt>~A</tt>" (escape-string (string-downcase part))))
                     ((eq part '&body)
                      ;; we don't really write '&BODY', we write it
                      ;; like in the CLHS
                      (setq body-seen t
                            after-required-args-p t)
                      (write-string "declaration* statement*"))
                     (t
                      (let ((specializer (pop specializers)))
                        (cond ((and specializer (not (eq specializer t)))
                               ;; add specializers if there are any left
                               (write-string (escape-string
                                              (string-downcase
                                               (format nil "(~A ~A)" part specializer)))))
                              (t (write-string (escape-string (string-downcase part)))))))))))))

(defun write-lambda-list (lambda-list &key (resultp t) specializers)
  "Writes the lambda list LAMBDA-LIST, optionally with the
specializers SPECIALIZERS.  Adds something like `=> result' at
the end if RESULTP is true."
  (write-string "<i>")
  (write-lambda-list* lambda-list specializers)
  (write-string "</i>")
  (when resultp
    (write-string " =&gt; <i>result</i></a>")))

(defun write-macro-entry (symbol lambda-list doc-string)
  "Writes a full documentation entry for the macro SYMBOL."
  (write-entry-header symbol "Macro")
  (format t "<b>~A</b> " (string-downcase symbol))
  (write-lambda-list lambda-list)
  (write-entry-footer symbol doc-string))

(defun write-function-entry (name lambda-list doc-string other-entries
                                  &key genericp signature-only-p specializers qualifiers)
  "Writes a full documentation entry for the function, generic
function, or method with name NAME.  NAME is a generic function
if GENERICP is true, SPECIALIZERS is a list of specializers,
i.e. in this case NAME is a method.  Likewise, QUALIFIERS is a
list of qualifiers.  SIGNATURE-ONLY-P means that we don't want a
full header."
  (let* ((setfp (consp name))
         (symbol (if setfp (second name) name))
         (type (cond (specializers :method)
                     (genericp :generic-function)
                     (t :function)))
         ;; check if this is a reader for which there is a writer (so
         ;; we have an accessor) with the same signature
         (writer (and (not setfp)
                      (find-if (lambda (entry)
                                 (and (equal `(setf ,name) (first entry))
                                      (eq type (second entry))
                                      (or (null specializers)
                                          (equal specializers (rest (fifth entry))))))
                               other-entries)))
         (resultp (and (not setfp)
                       (null (intersection '(:before :after)
                                           qualifiers)))))    
    (cond (signature-only-p
           (write-string "<a class=none>"))
          (t
           (write-entry-header name (if writer
                                      (ecase type
                                        (:method "Specialized accessor")
                                        (:generic-function "Generic accessor")
                                        (:function "Accessor"))
                                      (ecase type
                                        (:method "Method")
                                        (:generic-function "Generic function")
                                        (:function "Function")))
                               :write-name-p (null specializers))))
    (cond (setfp
           (format t "<tt>(setf (</tt><b>~A</b> " (string-downcase symbol))
           (write-lambda-list (rest lambda-list) :resultp resultp :specializers (rest specializers))
           (write-string "<tt>)</tt> ")
           ;; we should use the specializer here as well
           (format t "<i>~A</i>" (string-downcase (first lambda-list)))
           (write-string "<tt>)</tt></a>")
           (format t "~(~{<tt> ~S</tt>~^~}~)" qualifiers))
          (t (format t "<b>~A</b> " (string-downcase symbol))
             (write-lambda-list lambda-list :specializers specializers :resultp resultp)
             (format t "~(~{<tt> ~S</tt>~^~}~)" qualifiers)))
    (when writer
      ;; if this is an accessor, the add the writer immediately after
      ;; the reader..
      (format t "~%<br>")
      (destructuring-bind (name doc-type lambda-list doc-string &optional specializers qualifiers)
          writer
        (declare (ignore doc-type doc-string))
        (write-function-entry name lambda-list nil nil
                              :signature-only-p t
                              :specializers specializers
                              :qualifiers qualifiers))
      ;; ...and remove it from the list of entries which haven't been
      ;; written yet
      (setq other-entries (remove writer other-entries))))
  (unless signature-only-p
    (write-entry-footer name doc-string))
  other-entries)

(defun write-entry (entry other-entries)
  "Write one documentation entry corresponding to ENTRY.
OTHER-ENTRIES is the list of the remaining entries waiting to be
written.  OTHER-ENTRIES, probably updated, will be returned."
  (destructuring-bind (name doc-type lambda-list doc-string &optional specializers qualifiers)
      entry
    (unless (or (consp name) specializers)
      ;; add NAME to index list unless it's a SETF name or the name of
      ;; a method
      (push name *symbols*))
    (ecase doc-type
      (:constant (write-constant-entry name doc-string))
      (:special-var (write-special-var-entry name doc-string))
      (:class (write-class-entry name doc-string))
      (:macro (write-macro-entry name lambda-list doc-string))
      (:function (setq other-entries
                       (write-function-entry name lambda-list doc-string other-entries)))
      (:generic-function (setq other-entries
                               (write-function-entry name lambda-list doc-string other-entries
                                                     :genericp t)))
      (:method (setq other-entries
                     (write-function-entry name lambda-list doc-string other-entries
                                           :specializers specializers
                                           :qualifiers qualifiers)))))
  other-entries)

(defun write-page-header (package-name subtitle symbols)
  "Writes the header of the HTML page.  Assumes that the library
has the same name as the package.  Adds a list of all exported
symbols with links."
  (format t "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">
<html> 

<head>
  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">
  <title>~A - ~A</title>
  <style type=\"text/css\">
  pre { padding:5px; background-color:#e0e0e0 }
  h3, h4 { text-decoration: underline; }
  a { text-decoration: none; padding: 1px 2px 1px 2px; }
  a:visited { text-decoration: none; padding: 1px 2px 1px 2px; }
  a:hover { text-decoration: none; padding: 1px 1px 1px 1px; border: 1px solid #000000; } 
  a:focus { text-decoration: none; padding: 1px 2px 1px 2px; border: none; }
  a.none { text-decoration: none; padding: 0; }
  a.none:visited { text-decoration: none; padding: 0; } 
  a.none:hover { text-decoration: none; border: none; padding: 0; } 
  a.none:focus { text-decoration: none; border: none; padding: 0; } 
  a.noborder { text-decoration: none; padding: 0; } 
  a.noborder:visited { text-decoration: none; padding: 0; } 
  a.noborder:hover { text-decoration: none; border: none; padding: 0; } 
  a.noborder:focus { text-decoration: none; border: none; padding: 0; }  
  pre.none { padding:5px; background-color:#ffffff }
  </style>
</head>

<body bgcolor=white>

<h2> ~2:*~A - ~A</h2>

<blockquote>
<br>&nbsp;<br><h3><a name=abstract class=none>Abstract</a></h3>

The code comes with
a <a
href=\"http://www.opensource.org/licenses/bsd-license.php\">BSD-style
license</a> so you can basically do with it whatever you want.

<p>
<font color=red>Download shortcut:</font> <a href=\"http://weitz.de/files/~A.tar.gz\">http://weitz.de/files/~:*~A.tar.gz</a>.
</blockquote>

<br>&nbsp;<br><h3><a class=none name=\"contents\">Contents</a></h3>
<ol>
  <li><a href=\"#download\">Download</a>
  <li><a href=\"#dictionary\">The ~A dictionary</a>
    <ol>
~{      <li><a href=\"#~A\"><code>~:*~A</code></a>
~}    </ol>
  <li><a href=\"#ack\">Acknowledgements</a>
</ol>

<br>&nbsp;<br><h3><a class=none name=\"download\">Download</a></h3>

~2:*~A together with this documentation can be downloaded from <a
href=\"http://weitz.de/files/~2:*~A.tar.gz\">http://weitz.de/files/~:*~A.tar.gz</a>. The
current version is 0.1.0.

<br>&nbsp;<br><h3><a class=none name=\"dictionary\">The ~A dictionary</a></h3>

"
          package-name subtitle (string-downcase package-name)
          package-name symbols))

(defun write-page-footer ()
  "Writes the footer of the HTML page."
  (write-string "

<br>&nbsp;<br><h3><a class=none name=\"ack\">Acknowledgements</a></h3>

<p>
This documentation was prepared with <a href=\"http://weitz.de/documentation-template/\">DOCUMENTATION-TEMPLATE</a>.
</p>
<p>
$Header: /usr/local/cvsrep/documentation-template/output.lisp,v 1.17 2010/08/05 19:24:27 edi Exp $
<p><a href=\"http://weitz.de/index.html\">BACK TO MY HOMEPAGE</a>

</body>
</html>"))

(defun create-template (package &key (target (or *target*
                                                 #-:lispworks (error "*TARGET* not specified.")
                                                 #+:lispworks
                                                 (capi:prompt-for-file "Select an output target:"
                                                                       :operation :save
                                                                       :filters '("HTML Files" "*.HTML;*.HTM"
                                                                                  "All Files" "*.*")
                                                                       :filter "*.HTML;*.HTM")))
                                     (subtitle "a cool library")
                                     ((:maybe-skip-methods-p *maybe-skip-methods-p*)
                                      *maybe-skip-methods-p*)
                                     (if-exists :supersede)
                                     (if-does-not-exist :create))
  "Writes an HTML page with preliminary documentation entries and an
index for all exported symbols of the package PACKAGE to the file
TARGET.  If MAYBE-SKIP-METHODS-P is true, documentation entries for
inidividual methods are skipped if the corresponding generic function
has a documentation string."
  (when target
    (setq *target* target))
  (let (*symbols*)
    (with-open-file (*standard-output* target
                                       :direction :output
                                       :if-exists if-exists
                                       :if-does-not-exist if-does-not-exist)
      (let ((body
             (with-output-to-string (*standard-output*)
               (let ((entries (collect-all-doc-entries package)))
                 (loop
                  (let ((entry (or (pop entries) (return))))
                    (setq entries (write-entry entry entries))))))))
        (write-page-header (package-name package) subtitle
                           (mapcar #'string-downcase (reverse *symbols*)))
        (write-string body)
        (write-page-footer))))
  (values))