
(in-package :common-lisp-user)

(defpackage :editor-hints.named-readtables
  (:use :common-lisp)
  (:nicknames :named-readtables)
  (:export
   #:defreadtable
   #:in-readtable
   #:make-readtable
   #:merge-readtables-into
   #:find-readtable
   #:ensure-readtable
   #:rename-readtable
   #:readtable-name
   #:register-readtable
   #:unregister-readtable
   #:copy-named-readtable
   #:list-all-named-readtables
   ;; Types
   #:named-readtable-designator
   ;; Conditions
   #:reader-macro-conflict
   #:readtable-does-already-exist
   #:readtable-does-not-exist
   )
  (:documentation
   "
* What are Named-Readtables?

  Named-Readtables is a library that provides a namespace for
  readtables akin to the already-existing namespace of packages. In
  particular:

     * you can associate readtables with names, and retrieve
       readtables by names;

     * you can associate source files with readtable names, and be
       sure that the right readtable is active when compiling/loading
       the file;

     * similiarly, your development environment now has a chance to
       automatically determine what readtable should be active while
       processing source forms on interactive commands. (E.g. think of
       `C-c C-c' in Slime [yet to be done])

  It follows that Named-Readtables is a facility for using readtables in
  a localized way.

  Additionally, it also attempts to become a facility for using
  readtables in a _modular_ way. In particular:

     * it provides a macro to specify the content of a readtable at a
       glance;

     * it makes it possible to use multiple inheritance between readtables.

* Notes on the API

  The API heavily imitates the API of packages. This has the nice
  property that any experienced Common Lisper will take it up without
  effort.

      DEFREADTABLE              -   DEFPACKAGE

      IN-READTABLE              -   IN-PACKAGE

      MERGE-READTABLES-INTO     -   USE-PACKAGE

      MAKE-READTABLE            -   MAKE-PACKAGE

      UNREGISTER-READTABLE      -   DELETE-PACKAGE

      RENAME-READTABLE          -   RENAME-PACKAGE

      FIND-READTABLE            -   FIND-PACKAGE

      READTABLE-NAME            -   PACKAGE-NAME

      LIST-ALL-NAMED-READTABLES -   LIST-ALL-PACKAGES

* Important API idiosyncrasies

  There are three major differences between the API of Named-Readtables,
  and the API of packages.

   1. Readtable names are symbols not strings.

        Time has shown that the fact that packages are named by
        strings causes severe headache because of the potential of
        package names colliding with each other.

        Hence, readtables are named by symbols lest to make the
        situation worse than it already is. Consequently, readtables
        named CL-ORACLE:SQL-SYNTAX and CL-MYSQL:SQL-SYNTAX can
        happily coexist next to each other. Or, taken to an extreme,
        SCHEME:SYNTAX and ELISP:SYNTAX.

        If, for example to duly signify the importance of your cool
        readtable hack, you really think it deserves a global name,
        you can always resort to keywords.

   2. The inheritance is resolved statically, not dynamically.

        A package that uses another package will have access to all
        the other package's exported symbols, even to those that will
        be added after its definition. I.e. the inheritance is
        resolved at run-time, that is dynamically.

        Unfortunately, we cannot do the same for readtables in a
        portable manner.

        Therefore, we do not talk about \"using\" another readtable
        but about \"merging\" the other readtable's definition into
        the readtable we are going to define. I.e. the inheritance is
        resolved once at definition time, that is statically.

        (Such merging can more or less be implemented portably albeit
        at a certain cost. Most of the time, this cost manifests
        itself at the time a readtable is defined, i.e. once at
        compile-time, so it may not bother you.  Nonetheless, we
        provide extra support for Sbcl, ClozureCL, and AllegroCL at
        the moment. Patches for your implementation of choice are
        welcome, of course.)

   3. DEFREADTABLE does not have compile-time effects.

        If you define a package via DEFPACKAGE, you can make that
        package the currently active package for the subsequent
        compilation of the same file via IN-PACKAGE. The same is,
        however, not true for DEFREADTABLE and IN-READTABLE for the
        following reason:

        It's unlikely that the need for special reader-macros arises
        for a problem which can be solved in just one file. Most
        often, you're going to define the reader macro functions, and
        set up the corresponding readtable in an extra file.

        If DEFREADTABLE had compile-time effects, you'd have to wrap
        each definition of a reader-macro function in an EVAL-WHEN to
        make its definition available at compile-time. Because that's
        simply not the common case, DEFREADTABLE does not have a
        compile-time effect.

        If you want to use a readtable within the same file as its
        definition, wrap the DEFREADTABLE and the reader-macro
        function definitions in an explicit EVAL-WHEN.

* Preregistered Readtables

    - NIL, :STANDARD, and :COMMON-LISP designate the /standard readtable/.

    - :MODERN designates a _case-preserving_ /standard-readtable/.

    - :CURRENT designates the /current readtable/.

* Examples

    > (defreadtable elisp:syntax
    >    (:merge :standard)
    >    (:macro-char #\\? #'elisp::read-character-literal t)
    >    (:macro-char #\\[ #'elisp::read-vector-literal t)
    >    ...
    >    (:case :preserve))
    >
    > (defreadtable scheme:syntax
    >    (:merge :standard)
    >    (:macro-char #\\[ #'(lambda (stream char)
    >                          (read-delimited-list #\\] stream)))
    >    (:macro-char #\\# :dispatch)
    >    (:dispatch-macro-char #\\# #\\t #'scheme::read-#t)
    >    (:dispatch-macro-char #\\# #\\f #'scheme::read-#f)
    >    ...
    >    (:case :preserve))
    >
    > (in-readtable elisp:syntax)
    >
    > ...
    >
    > (in-readtable scheme:syntax)
    >
    > ...

* Acknowledgements

  Thanks to Robert Goldman for making me want to write this library.

  Thanks to Stephen Compall, Ariel Badichi, David Lichteblau, Bart
  Botta, David Crawford, and Pascal Costanza for being early adopters,
  providing comments and bugfixes.
"))

(pushnew :named-readtables *features*)