lisp-openshift
==============

This package provides everything you need to start hosting Common
Lisp-based web applications on OpenShift, Red Hat's free, auto-scaling
Platform as a Service (PaaS) cloud solution.

The default app template uses SBCL and a quicklisp-based dev platform
with the hunchentoot web server.

lisp-openshift will auto-provision a lisp environment into your DIY
OpenShift project.  It does this by downloading and extracting the
contents of the SBCL RPM package from the Fedora Project's Extra
Packages for Enterprise Linux (EPEL) repository.  This package is
installed in your application's persistent `data` directory.

Running on OpenShift
--------------------

Create an account at http://openshift.redhat.com/

Install your command line tools as instructed at https://www.openshift.com/get-started#cli

Create a DIY application

    rhc app create -a myapp -t diy-0.1

Add this upstream lisp-openshift repo

    cd myapp
    git remote add upstream -m master git://github.com/atgreen/lisp-openshift.git
    git pull -s recursive -X theirs upstream master

Then push the repo upstream

    git push

That's it!  You can now have a look at your application here:

    http://myapp-$namespace.rhcloud.com
 
To see it in action, check out http://lisp2-atgreen.rhcloud.com.


Using SBCL and Emacs
--------------------

Start SBCL with HOME set to application's current directory.

    $ HOME=`pwd` sbcl
    This is SBCL 1.0.51-1.fc16, an implementation of ANSI Common Lisp.
    More information about SBCL is available at <http://www.sbcl.org/>.
    
    SBCL is free software, provided as is, with absolutely no warranty.
    It is mostly in the public domain; some portions are provided under
    BSD-style licenses.  See the CREDITS and COPYING files in the
    distribution for more information.

I have modified application's .sbclrc to start swank server at port 4005,
so when you start Emacs you need to do M-x slime-connect and confirm default values.
Now you can use your Emacs' REPL to talk to your application.

Using application's own Quicklisp
---------------------------------

Quicklisp is a library manager for Common Lisp.  This project contains
a Quicklisp repository of core packages for simple web applications,
however, the upstream Quicklisp project hosts over 700 libraries.

To install more libraries into your project's repository, simply use 
`ql:quickload` as usual.

    * (ql:quickload :cl-mongo)

This would add the cl-mongo package to your application.

Links
-----

* http://openshift.redhat.com
* http://www.quicklisp.org
* http://www.sbcl.org
* http://weitz.de/hunchentoot
* http://www.fedoraproject.org/wiki/EPEL
* http://linkedin.com/in/green


__Happy hacking!__

Anthony Green


