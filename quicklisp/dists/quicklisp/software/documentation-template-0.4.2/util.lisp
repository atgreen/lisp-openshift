;;; -*- Mode: LISP; Syntax: COMMON-LISP; Package: DOCUMENTATION-TEMPLATE; Base: 10 -*-
;;; $Header: /usr/local/cvsrep/documentation-template/util.lisp,v 1.14 2010/08/05 19:24:27 edi Exp $

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

;;; For the purpose of this file, an "entry" is a list of four or five
;;; symbols - a name, a keyword for the kind of the entry, a lambda
;;; list (for functions and macros), a documentation string, and
;;; optionally a list of specializers

#+(or :sbcl :allegro)
(defun function-lambda-list (function)
  "Returns the lambda list of the function designator FUNCTION."
  #+:sbcl
  (sb-introspect:function-lambda-list function)
  #+:allegro
  (excl:arglist function))
    
(defun symbol-constant-p (symbol)
  "Returns true if SYMBOL is a constant."
  #+:lispworks (sys:symbol-constant-p symbol)
  #-:lispworks (constantp symbol))

(defun declared-special-p (symbol)
  "Returns true if SYMBOL is declared special."
  #+:lispworks (sys:declared-special-p symbol)
  #+:sbcl (eql :special (sb-int:info :variable :kind symbol))
  #+:allegro (eq (sys:variable-information symbol) :special))

(defun constant-doc-entry (symbol)
  "Returns a list with one entry for a constant if SYMBOL names a
constant."
  (when (symbol-constant-p symbol)
    (list (list symbol :constant nil (documentation symbol 'variable)))))

(defun special-var-doc-entry (symbol)
  "Returns a list with one entry for a special variable if SYMBOL
names a special variable."
  ;; skip constants because SYS:DECLARED-SPECIAL-P is true for them as
  ;; well
  (when (and (not (symbol-constant-p symbol))
             (declared-special-p symbol))
    (list (list symbol :special-var nil (documentation symbol 'variable)))))

(defun class-doc-entry (symbol)
  "Returns a list with one entry for a class if SYMBOL names a
class."
  (when (find-class symbol nil)
    (list (list symbol :class nil (documentation symbol 'type)))))

(defun macro-doc-entry (symbol)
  "Returns a list with one entry for a macro if SYMBOL names a
macro."
  (when (and (fboundp symbol)
             (macro-function symbol))
    (list (list symbol :macro (function-lambda-list symbol)
                (documentation symbol 'function)))))

#+:sbcl
(defgeneric %sbcl-simple-specializer (specializer)
  (:documentation "Returns a simple representation of
SPECIALIZER.")
  (:method (specializer)
    (class-name specializer))
  (:method ((specializer eql-specializer))
    `(eql ,(eql-specializer-object specializer))))

(defun simplify-specializer (specializer)
  "Converts specializers which are classes to their names, leaves
the rest alone."
  (or (ignore-errors #+(or :lispworks :allegro) (class-name specializer)
                     #+:sbcl (%sbcl-simple-specializer specializer))
      specializer))

(defun generic-function-doc-entry (name)
  "Returns a list with one entry for a generic function and one
entry for each of its methods if NAME names a generic function."
  (when (and (fboundp name)
             (typep (fdefinition name) 'standard-generic-function))
    (let* ((lambda-list (function-lambda-list name))
           (generic-function-documentation (documentation name 'function))
           (generic-function-entry           
            (list name :generic-function lambda-list
                  generic-function-documentation)))
      (cond ((and generic-function-documentation *maybe-skip-methods-p*)
             (list generic-function-entry))
            (t (cons generic-function-entry                     
                     (loop for method in (generic-function-methods (fdefinition name))
                           collect (list name :method lambda-list
                                         (documentation method t)
                                         (mapcar #'simplify-specializer (method-specializers method))
                                         (method-qualifiers method)))))))))

(defun function-doc-entry (name)
  "Returns a list with one entry for a function if NAME names a
plain old function."
  (when (and (fboundp name)
             ;; no macros
             (or (listp name)
                 (not (macro-function name)))
             ;; no generic functions
             (not (typep (fdefinition name) 'standard-generic-function)))
    (list (list name :function (function-lambda-list name)
                (documentation name 'function)))))

(defun doc-entries (symbol)
  "Returns a list of all possible entries for the symbol SYMBOL
and for the corresponding SETF function name."
  (let ((setf-name `(setf ,symbol)))
    `(,@(constant-doc-entry symbol)
      ,@(special-var-doc-entry symbol)
      ,@(class-doc-entry symbol)
      ,@(macro-doc-entry symbol)
      ,@(generic-function-doc-entry symbol)
      ,@(function-doc-entry symbol)
      ,@(generic-function-doc-entry setf-name)
      ,@(function-doc-entry setf-name))))

(defun doc-type-ordinal (type)
  "Assigns ordinals to the different kinds of entries for sorting
purposes."
  (ecase type
    (:constant 0)
    (:special-var 1)
    (:class 2)
    (:macro 3)
    (:function 4)
    (:generic-function 5)
    (:method 6)))

(defun name= (name1 name2)
  "Two function names are equal if they are EQUAL - this covers
symbols as well as general function names."
  (equal name1 name2))

(defun name< (name1 name2)
  "Comparison function used for sorting - symbols are \"smaller\"
then SETF names, otherwise sort alphabetically."
  (or (and (consp name2)
           (atom name1))
      (and (consp name1)
           (consp name2)
           (string< (second name1) (second name2)))
      (and (atom name1)
           (atom name2)
           (string< name1 name2))))

(defun doc-entry< (entry1 entry2)
  "Comparions function used for sorting - sort by name and, if
the names are the same, by DOC-TYPE-ORDINAL."
  (or (name< (first entry1) (first entry2))
      (and (name= (first entry1) (first entry2))
           (< (doc-type-ordinal (second entry1))
              (doc-type-ordinal (second entry2))))))

(defun collect-all-doc-entries (package)
  "Returns a sorted list of entries for all exported symbols of
PACKAGE."
  (let (result)
    (do-external-symbols (symbol package (sort result #'doc-entry<))
      (setq result (nconc (doc-entries symbol) result)))))
