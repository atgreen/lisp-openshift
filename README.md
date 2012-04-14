lisp-openshift
==============

This package installs all of the necessary bits on Red Hat's OpenShift
hosting platform required to run hunchentoot based web applications in
the Red Hat's free OpenShift express hosting platform.

Here are the installation steps:

* Create an account on http://openshift.redhat.com.
* Create a DYI app. Let's call it myapp-mynamespace.
* Upload all of the persistent sbcl bits using the lisp-openshift  provided upload-sbcl script.
* Checkout myapp-mynamespace app from openshift's git repo.
* cd into that directory and run lisp-openshift's init-app script.
* commit and push your app, then wait for it to build.

Now point your browser at http://myapp-mynamespace.rhcloud.com and you
should see the default hunchentoot web page.

To see it in action, check out http://lisp2-atgreen.rhcloud.com.
