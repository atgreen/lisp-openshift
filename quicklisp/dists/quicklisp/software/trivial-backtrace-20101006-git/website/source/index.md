{include resources/header.md}

<div class="contents">
<div class="system-links">

  * [Mailing Lists][mailing-list]
  * [Getting it][downloads]
  * [Documentation][]
  * [News][]
  * [Test results][tr]
  * [Changelog][]

</div>
<div class="system-description">

### What it is

On of the many things that didn't quite get into the Common
Lisp standard was how to get a Lisp to output its call stack
when something has gone wrong. As such, each Lisp has
developed its own notion of what to display, how to display
it, and what sort of arguments can be used to customize it.
`trivial-backtrace` is a simple solution to generating a
backtrace portably. As of {today}, it supports Allegro Common
Lisp, LispWorkds, ECL, MCL, SCL, SBCL and CMUCL. Its
interface consists of three functions and one variable:

 * print-backtrace
 * print-backtrace-to-stream
 * print-condition
 * \*date-time-format\*

You can probably already guess what they do, but they are
described in more detail below.

{anchor mailing-lists}

### Mailing Lists

  * [trivial-backtrace-devel][devel-list]: A list for
    announcements, questions, patches, bug reports, and so
    on; It's for anything and everything

### API

{set-property docs-package trivial-backtrace}
{docs print-backtrace}
{docs print-backtrace-to-stream}
{docs print-condition}
{docs *date-time-format*}

{anchor downloads}

### Where is it

A [darcs][] repository is available. The commands to get it are
listed below:

    darcs get http://common-lisp.net/project/trivial-backtrace/

trivial-backtrace is also [ASDF installable][asdf-install].
Its CLiki home is right [where][cliki-home] you'd expect.

There's also a handy [gzipped tar file][tarball].


{anchor news}

### What is happening

<dl>
<dt>1 June 2008</dt>
<dd>Release version 1.0
    </dd>
    </dl>
</div>
</div>

{include resources/footer.md}

