(in-package :crypto-tests)

(defun hex-string-to-byte-array (string &key (start 0) (end nil))
  ;; This function disappears from profiles if SBCL can inline the
  ;; POSITION call, so declare SPEED high enough to trigger that.
  (declare (type string string) (optimize (speed 2)))
  (let* ((end (or end (length string)))
         (length (/ (- end start) 2))
         (key (make-array length :element-type '(unsigned-byte 8))))
    (declare (type (simple-array (unsigned-byte 8) (*)) key))
    (flet ((char-to-digit (char)
             (let ((x (cl:position char "0123456789abcdef"
                                   :test #'char-equal)))
               (or x (error "Invalid hex key ~A specified" string)))))
      (loop for i from 0
            for j from start below end by 2
            do (setf (aref key i)
                     (+ (* (char-to-digit (char string j)) 16)
                        (char-to-digit (char string (1+ j)))))
            finally (return key)))))


;;; test vector files

(defun test-vector-filename (ident)
  (merge-pathnames (make-pathname :directory '(:relative "test-vectors")
                                  :name (format nil "~(~A~)" ident)
                                  :type "testvec")
                   #.*compile-file-pathname*))

(defun sharp-a (stream sub-char numarg)
  (declare (ignore sub-char numarg))
  (crypto:ascii-string-to-byte-array (read stream t nil t)))

(defun sharp-h (stream sub-char numarg)
  (declare (ignore sub-char numarg))
  (hex-string-to-byte-array (read stream t nil t)))

(defun run-test-vector-file (name function-map)
  (let ((filename (test-vector-filename name))
        (*readtable* (copy-readtable)))
    (set-dispatch-macro-character #\# #\a #'sharp-a *readtable*)
    (set-dispatch-macro-character #\# #\h #'sharp-h *readtable*)
    (with-open-file (stream filename :direction :input
                            :element-type 'character
                            :if-does-not-exist :error)
      (loop for form = (read stream nil stream)
         until (eq form stream) do
         (cond
           ((not (listp form))
            (error "Invalid form in test vector file ~A: ~A" filename form))
           (t
            (let ((test-function (cdr (assoc (car form) function-map))))
              (unless test-function
                (error "No test function defined for ~A" (car form)))
              (apply test-function name (cdr form)))))
         finally (return t)))))

;;; cipher testing

(defun ecb-mode-test (cipher-name hexkey hexinput hexoutput)
  (cipher-test-guts cipher-name :ecb hexkey hexinput hexoutput))

(defun stream-mode-test (cipher-name hexkey hexinput hexoutput)
  (cipher-test-guts cipher-name :stream hexkey hexinput hexoutput))

(defparameter *cipher-tests*
  (list (cons :ecb-mode-test 'ecb-mode-test)
        (cons :stream-mode-test 'stream-mode-test)))

(defun cipher-test-guts (cipher-name mode key input output)
  (labels ((frob-hex-string (func input)
             (let ((cipher (crypto:make-cipher cipher-name :key key
                                               :mode mode))
                    (scratch (copy-seq input)))
               (funcall func cipher input scratch)
               scratch))
           (cipher-test (func input output)
             (not (mismatch (frob-hex-string func input) output))))
    (unless (cipher-test 'crypto:encrypt input output)
      (error "encryption failed for ~A on key ~A, input ~A, output ~A"
             cipher-name key input output))
    (unless (cipher-test 'crypto:decrypt output input)
      (error "decryption failed for ~A on key ~A, input ~A, output ~A"
             cipher-name key output input))))

;;; encryption mode consistency checking

;;; tests from NIST

(defun mode-test (mode cipher-name key iv input output)
  (labels ((frob-hex-string (cipher func input)
             (let ((scratch (copy-seq input)))
               (funcall func cipher input scratch)
               scratch))
           (cipher-test (cipher func input output)
             (not (mismatch (frob-hex-string cipher func input) output))))
    (let ((cipher (crypto:make-cipher cipher-name :key key :mode mode
                                      :initialization-vector iv)))
      (unless (cipher-test cipher 'crypto:encrypt input output)
        (error "encryption failed for ~A on key ~A, input ~A, output ~A"
               cipher-name key input output))
      (reinitialize-instance cipher :key key :mode mode
                             :initialization-vector iv)
      (unless (cipher-test cipher 'crypto:decrypt output input)
        (error "decryption failed for ~A on key ~A, input ~A, output ~A"
               cipher-name key output input)))))

(defparameter *mode-tests*
  (list (cons :mode-test 'mode-test)))


;;; digest testing routines

(defun digest-test/base (digest-name input expected-digest)
  (let ((result (crypto:digest-sequence digest-name input)))
    (when (mismatch result expected-digest)
      (error "one-shot ~A digest of ~S failed" digest-name input))))

(defun digest-test/incremental (digest-name input expected-digest)
  (loop with length = (length input)
     with digester = (crypto:make-digest digest-name)
     for i from 0 below length
     do (crypto:update-digest digester input :start i :end (1+ i))
     finally
     (let ((result (crypto:produce-digest digester)))
       (when (mismatch result expected-digest)
         (error "incremental ~A digest of ~S failed" digest-name input)))))

#+(or sbcl cmucl)
(defun digest-test/fill-pointer (digest-name octets expected-digest)
  (let* ((input (let ((x (make-array (* 2 (length octets))
                                     :fill-pointer 0
                                     :element-type '(unsigned-byte 8))))
                  (dotimes (i (length octets) x)
                    (vector-push (aref octets i) x))))
         (result (crypto:digest-sequence digest-name input)))
    (when (mismatch result expected-digest)
      (error "fill-pointer'd ~A digest of ~S failed" digest-name input))))

#+(or lispworks sbcl cmucl openmcl allegro)
(defun digest-test/stream (digest-name input expected-digest)
  (let* ((stream (crypto:make-digesting-stream digest-name)))
    (write-sequence input stream)
    (when (mismatch (crypto:produce-digest stream) expected-digest)
      (error "stream-y ~A digest of ~S failed" digest-name input))))

(defun digest-test/reinitialize-instance (digest-name input expected-digest)
  (let* ((digest (crypto:make-digest digest-name))
         (result (progn
                   (crypto:digest-sequence digest input)
                   (crypto:digest-sequence (reinitialize-instance digest) input))))
    (when (mismatch result expected-digest)
      (error "testing reinitialize-instance ~A digest of ~S failed" digest-name input))))

(defun digest-bit-test (digest-name leading byte trailing expected-digest)
  (let* ((input (let ((vector (make-array (+ 1 leading trailing)
                                          :element-type '(unsigned-byte 8)
                                          :initial-element 0)))
                  (setf (aref vector leading) byte)
                  vector))
         (result (crypto:digest-sequence digest-name input)))
    (when (mismatch result expected-digest)
      (error "individual bit test ~A digest of (~D #x~2,'0X ~D) failed"
             digest-name leading byte trailing))))

(defparameter *digest-tests*
  (list (cons :digest-test 'digest-test/base)
        (cons :digest-bit-test 'digest-bit-test)))

(defun ignore-test (&rest args)
  (declare (ignore args))
  nil)

(defparameter *digest-incremental-tests*
  (list (cons :digest-test 'digest-test/incremental)
        (cons :digest-bit-test 'ignore-test)))

#+(or sbcl cmucl)
(defparameter *digest-fill-pointer-tests*
  (list (cons :digest-test 'digest-test/fill-pointer)
        (cons :digest-bit-test 'ignore-test)))

#+(or lispworks sbcl cmucl openmcl allegro)
(defparameter *digest-stream-tests*
  (list (cons :digest-test 'digest-test/stream)
        (cons :digest-bit-test 'ignore-test)))

(defparameter *digest-reinitialize-instance-tests*
  (list (cons :digest-test 'digest-test/reinitialize-instance)
        (cons :digest-bit-test 'ignore-test)))


;;; mac testing routines

(defun hmac-test (name digest-name key data expected-digest)
  (declare (ignore name))
  (let ((hmac (ironclad:make-hmac key digest-name)))
    (ironclad:update-hmac hmac data)
    (when (mismatch expected-digest (ironclad:hmac-digest hmac))
      (error "HMAC/~A failed on key ~A, input ~A, output ~A"
             digest-name key data expected-digest))
    (loop
       initially (reinitialize-instance hmac :key key)
       for i from 0 below (length data)
       do (ironclad:update-hmac hmac data :start i :end (1+ i))
       (ironclad:hmac-digest hmac)
       finally (when (mismatch expected-digest (ironclad:hmac-digest hmac))
                 (error "progressive HMAC/~A failed on key ~A, input ~A, output ~A"
                        digest-name key data expected-digest)))))

(defun cmac-test (name cipher-name key data expected-digest)
  (declare (ignore name))
  (let ((cmac (ironclad:make-cmac key cipher-name)))
    (ironclad:update-cmac cmac data)
    (when (mismatch expected-digest (ironclad:cmac-digest cmac))
      (error "CMAC/~A failed on key ~A, input ~A, output ~A"
             cipher-name key data expected-digest))))

(defparameter *mac-tests*
  (list (cons :hmac-test 'hmac-test)
        (cons :cmac-test 'cmac-test)))
