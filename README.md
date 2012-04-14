lisp-openshift
==============

This package provides everything you need to start hosting Common
Lisp-based web applications on OpenShift, Red Hat's free, auto-scaling
Platform as a Service (PaaS) cloud solution.

The default app template uses SBCL and a quicklisp-based dev platform
with the hunchentoot web server.

Here are the installation steps:

* Create an account on http://openshift.redhat.com.
* Create a DIY app. Let's call it myapp-mynamespace.
* Upload all of the persistent sbcl bits by running lisp-openshift's upload-sbcl script.
* Clone the myapp-mynamespace app from openshift's git repo.
* cd into your app's directory, and run lisp-openshift's init-app script.
* commit and push your app, then wait for it to build.

Now point your browser at your app's URL (provided by openshift) and
you should see the default hunchentoot web page.

Happy hacking!

To see it in action, check out http://lisp2-atgreen.rhcloud.com.
