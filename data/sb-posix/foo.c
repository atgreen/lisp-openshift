#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <netinet/tcp.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <netdb.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <termios.h>
#include <syslog.h>
#define SIGNEDP(x) (((x)-1)<0)
#define SIGNED_(x) (SIGNEDP(x)?"":"un")
int main(int argc, char *argv[]) {
    FILE *out;
    if (argc != 2) {
        printf("Invalid argcount!");
        return 1;
    } else
        out = fopen(argv[1], "w");
    if (!out) {
        printf("Error opening output file!");
        return 1;
    }
    fprintf (out, "(cl:in-package #:SB-POSIX)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel)\n");
    fprintf (out, "  (cl:defparameter *integer-sizes* (cl:make-hash-table))\n");
    fprintf (out, "  (cl:setf (cl:gethash %d *integer-sizes*) 'sb-alien:char)\n", sizeof(char));
    fprintf (out, "  (cl:setf (cl:gethash %d *integer-sizes*) 'sb-alien:short)\n", sizeof(short));
    fprintf (out, "  (cl:setf (cl:gethash %d *integer-sizes*) 'sb-alien:long)\n", sizeof(long));
    fprintf (out, "  (cl:setf (cl:gethash %d *integer-sizes*) 'sb-alien:int)\n", sizeof(int));
    fprintf (out, ")\n");
#ifdef AF_INET
    fprintf (out, "(cl:defconstant AF-INET %d \"IP Protocol family\")\n", AF_INET);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for AF_INET (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'AF-INET)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type UID-T (sb-alien:%ssigned %d)))\n", SIGNED_(uid_t), (8*sizeof(uid_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type GID-T (sb-alien:%ssigned %d)))\n", SIGNED_(gid_t), (8*sizeof(gid_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type NLINK-T (sb-alien:%ssigned %d)))\n", SIGNED_(nlink_t), (8*sizeof(nlink_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type PID-T (sb-alien:%ssigned %d)))\n", SIGNED_(pid_t), (8*sizeof(pid_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type INO-T (sb-alien:%ssigned %d)))\n", SIGNED_(ino_t), (8*sizeof(ino_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type TIME-T (sb-alien:%ssigned %d)))\n", SIGNED_(time_t), (8*sizeof(time_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type DEV-T (sb-alien:%ssigned %d)))\n", SIGNED_(dev_t), (8*sizeof(dev_t)));
#ifdef SIGHUP
    fprintf (out, "(cl:defconstant SIGHUP %d \"terminal line hangup.\")\n", SIGHUP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGHUP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGHUP)\n");
#ifdef SIGINT
    fprintf (out, "(cl:defconstant SIGINT %d \"interrupt program.\")\n", SIGINT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGINT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGINT)\n");
#ifdef SIGQUIT
    fprintf (out, "(cl:defconstant SIGQUIT %d \"quit program.\")\n", SIGQUIT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGQUIT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGQUIT)\n");
#ifdef SIGILL
    fprintf (out, "(cl:defconstant SIGILL %d \"illegal instruction.\")\n", SIGILL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGILL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGILL)\n");
#ifdef SIGTRAP
    fprintf (out, "(cl:defconstant SIGTRAP %d \"trace trap.\")\n", SIGTRAP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGTRAP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGTRAP)\n");
#ifdef SIGABRT
    fprintf (out, "(cl:defconstant SIGABRT %d \"abort program (formerly SIGIOT).\")\n", SIGABRT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGABRT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGABRT)\n");
#ifdef SIGEMT
    fprintf (out, "(cl:defconstant SIGEMT %d \"emulate instruction executed.\")\n", SIGEMT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGEMT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGEMT)\n");
#ifdef SIGFPE
    fprintf (out, "(cl:defconstant SIGFPE %d \"floating-point exception.\")\n", SIGFPE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGFPE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGFPE)\n");
#ifdef SIGKILL
    fprintf (out, "(cl:defconstant SIGKILL %d \"kill program.\")\n", SIGKILL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGKILL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGKILL)\n");
#ifdef SIGBUS
    fprintf (out, "(cl:defconstant SIGBUS %d \"bus error.\")\n", SIGBUS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGBUS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGBUS)\n");
#ifdef SIGSEGV
    fprintf (out, "(cl:defconstant SIGSEGV %d \"segmentation violation.\")\n", SIGSEGV);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGSEGV (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGSEGV)\n");
#ifdef SIGSYS
    fprintf (out, "(cl:defconstant SIGSYS %d \"non-existent system call invoked.\")\n", SIGSYS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGSYS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGSYS)\n");
#ifdef SIGPIPE
    fprintf (out, "(cl:defconstant SIGPIPE %d \"write on a pipe with no reader.\")\n", SIGPIPE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGPIPE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGPIPE)\n");
#ifdef SIGALRM
    fprintf (out, "(cl:defconstant SIGALRM %d \"real-time timer expired.\")\n", SIGALRM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGALRM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGALRM)\n");
#ifdef SIGTERM
    fprintf (out, "(cl:defconstant SIGTERM %d \"software termination signal.\")\n", SIGTERM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGTERM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGTERM)\n");
#ifdef SIGURG
    fprintf (out, "(cl:defconstant SIGURG %d \"urgent condition present on socket.\")\n", SIGURG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGURG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGURG)\n");
#ifdef SIGSTOP
    fprintf (out, "(cl:defconstant SIGSTOP %d \"stop (cannot be caught or ignored).\")\n", SIGSTOP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGSTOP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGSTOP)\n");
#ifdef SIGTSTP
    fprintf (out, "(cl:defconstant SIGTSTP %d \"stop signal generated from keyboard.\")\n", SIGTSTP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGTSTP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGTSTP)\n");
#ifdef SIGCONT
    fprintf (out, "(cl:defconstant SIGCONT %d \"continue after stop.\")\n", SIGCONT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGCONT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGCONT)\n");
#ifdef SIGCHLD
    fprintf (out, "(cl:defconstant SIGCHLD %d \"child status has changed.\")\n", SIGCHLD);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGCHLD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGCHLD)\n");
#ifdef SIGTTIN
    fprintf (out, "(cl:defconstant SIGTTIN %d \"background read attempted from control terminal.\")\n", SIGTTIN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGTTIN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGTTIN)\n");
#ifdef SIGTTOU
    fprintf (out, "(cl:defconstant SIGTTOU %d \"background write attempted to control terminal.\")\n", SIGTTOU);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGTTOU (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGTTOU)\n");
#ifdef SIGIO
    fprintf (out, "(cl:defconstant SIGIO %d \"I/O is possible on a descriptor (see fcntl(2)).\")\n", SIGIO);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGIO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGIO)\n");
#ifdef SIGXCPU
    fprintf (out, "(cl:defconstant SIGXCPU %d \"cpu time limit exceeded (see setrlimit(2)).\")\n", SIGXCPU);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGXCPU (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGXCPU)\n");
#ifdef SIGXFSZ
    fprintf (out, "(cl:defconstant SIGXFSZ %d \"file size limit exceeded (see setrlimit(2)).\")\n", SIGXFSZ);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGXFSZ (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGXFSZ)\n");
#ifdef SIGVTALRM
    fprintf (out, "(cl:defconstant SIGVTALRM %d \"virtual time alarm (see setitimer(2)).\")\n", SIGVTALRM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGVTALRM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGVTALRM)\n");
#ifdef SIGPROF
    fprintf (out, "(cl:defconstant SIGPROF %d \"profiling timer alarm (see setitimer(2)).\")\n", SIGPROF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGPROF (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGPROF)\n");
#ifdef SIGWINCH
    fprintf (out, "(cl:defconstant SIGWINCH %d \"Window size change.\")\n", SIGWINCH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGWINCH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGWINCH)\n");
#ifdef SIGPWR
    fprintf (out, "(cl:defconstant SIGPWR %d \"Power failure.\")\n", SIGPWR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGPWR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGPWR)\n");
#ifdef SIGUSR1
    fprintf (out, "(cl:defconstant SIGUSR1 %d \"User defined signal 1.\")\n", SIGUSR1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGUSR1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGUSR1)\n");
#ifdef SIGUSR2
    fprintf (out, "(cl:defconstant SIGUSR2 %d \"User defined signal 2.\")\n", SIGUSR2);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGUSR2 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGUSR2)\n");
#ifdef SIGRTMIN
    fprintf (out, "(cl:defconstant SIGRTMIN %d \"Smallest real-time signal number.\")\n", SIGRTMIN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGRTMIN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGRTMIN)\n");
#ifdef SIGRTMAX
    fprintf (out, "(cl:defconstant SIGRTMAX %d \"Largest real-time signal number.\")\n", SIGRTMAX);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SIGRTMAX (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SIGRTMAX)\n");
#ifdef EPERM
    fprintf (out, "(cl:defconstant EPERM %d \"NIL\")\n", EPERM);
    fprintf (out, "(cl:setf (get 'EPERM 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPERM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EPERM)\n");
#ifdef ENOENT
    fprintf (out, "(cl:defconstant ENOENT %d \"NIL\")\n", ENOENT);
    fprintf (out, "(cl:setf (get 'ENOENT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOENT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOENT)\n");
#ifdef ESRCH
    fprintf (out, "(cl:defconstant ESRCH %d \"NIL\")\n", ESRCH);
    fprintf (out, "(cl:setf (get 'ESRCH 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESRCH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ESRCH)\n");
#ifdef EINTR
    fprintf (out, "(cl:defconstant EINTR %d \"NIL\")\n", EINTR);
    fprintf (out, "(cl:setf (get 'EINTR 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EINTR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EINTR)\n");
#ifdef EIO
    fprintf (out, "(cl:defconstant EIO %d \"NIL\")\n", EIO);
    fprintf (out, "(cl:setf (get 'EIO 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EIO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EIO)\n");
#ifdef ENXIO
    fprintf (out, "(cl:defconstant ENXIO %d \"NIL\")\n", ENXIO);
    fprintf (out, "(cl:setf (get 'ENXIO 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENXIO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENXIO)\n");
#ifdef E2BIG
    fprintf (out, "(cl:defconstant E2BIG %d \"NIL\")\n", E2BIG);
    fprintf (out, "(cl:setf (get 'E2BIG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for E2BIG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'E2BIG)\n");
#ifdef ENOEXEC
    fprintf (out, "(cl:defconstant ENOEXEC %d \"NIL\")\n", ENOEXEC);
    fprintf (out, "(cl:setf (get 'ENOEXEC 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOEXEC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOEXEC)\n");
#ifdef EBADF
    fprintf (out, "(cl:defconstant EBADF %d \"NIL\")\n", EBADF);
    fprintf (out, "(cl:setf (get 'EBADF 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADF (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBADF)\n");
#ifdef ECHILD
    fprintf (out, "(cl:defconstant ECHILD %d \"NIL\")\n", ECHILD);
    fprintf (out, "(cl:setf (get 'ECHILD 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECHILD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECHILD)\n");
#ifdef EAGAIN
    fprintf (out, "(cl:defconstant EAGAIN %d \"NIL\")\n", EAGAIN);
    fprintf (out, "(cl:setf (get 'EAGAIN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAGAIN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EAGAIN)\n");
#ifdef ENOMEM
    fprintf (out, "(cl:defconstant ENOMEM %d \"NIL\")\n", ENOMEM);
    fprintf (out, "(cl:setf (get 'ENOMEM 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOMEM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOMEM)\n");
#ifdef EACCES
    fprintf (out, "(cl:defconstant EACCES %d \"NIL\")\n", EACCES);
    fprintf (out, "(cl:setf (get 'EACCES 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EACCES (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EACCES)\n");
#ifdef EFAULT
    fprintf (out, "(cl:defconstant EFAULT %d \"NIL\")\n", EFAULT);
    fprintf (out, "(cl:setf (get 'EFAULT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EFAULT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EFAULT)\n");
#ifdef ENOTBLK
    fprintf (out, "(cl:defconstant ENOTBLK %d \"NIL\")\n", ENOTBLK);
    fprintf (out, "(cl:setf (get 'ENOTBLK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTBLK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTBLK)\n");
#ifdef EBUSY
    fprintf (out, "(cl:defconstant EBUSY %d \"NIL\")\n", EBUSY);
    fprintf (out, "(cl:setf (get 'EBUSY 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBUSY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBUSY)\n");
#ifdef EEXIST
    fprintf (out, "(cl:defconstant EEXIST %d \"NIL\")\n", EEXIST);
    fprintf (out, "(cl:setf (get 'EEXIST 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EEXIST (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EEXIST)\n");
#ifdef EXDEV
    fprintf (out, "(cl:defconstant EXDEV %d \"NIL\")\n", EXDEV);
    fprintf (out, "(cl:setf (get 'EXDEV 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EXDEV (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EXDEV)\n");
#ifdef ENODEV
    fprintf (out, "(cl:defconstant ENODEV %d \"NIL\")\n", ENODEV);
    fprintf (out, "(cl:setf (get 'ENODEV 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENODEV (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENODEV)\n");
#ifdef ENOTDIR
    fprintf (out, "(cl:defconstant ENOTDIR %d \"NIL\")\n", ENOTDIR);
    fprintf (out, "(cl:setf (get 'ENOTDIR 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTDIR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTDIR)\n");
#ifdef EISDIR
    fprintf (out, "(cl:defconstant EISDIR %d \"NIL\")\n", EISDIR);
    fprintf (out, "(cl:setf (get 'EISDIR 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EISDIR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EISDIR)\n");
#ifdef EINVAL
    fprintf (out, "(cl:defconstant EINVAL %d \"NIL\")\n", EINVAL);
    fprintf (out, "(cl:setf (get 'EINVAL 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EINVAL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EINVAL)\n");
#ifdef ENFILE
    fprintf (out, "(cl:defconstant ENFILE %d \"NIL\")\n", ENFILE);
    fprintf (out, "(cl:setf (get 'ENFILE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENFILE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENFILE)\n");
#ifdef EMFILE
    fprintf (out, "(cl:defconstant EMFILE %d \"NIL\")\n", EMFILE);
    fprintf (out, "(cl:setf (get 'EMFILE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EMFILE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EMFILE)\n");
#ifdef ENOTTY
    fprintf (out, "(cl:defconstant ENOTTY %d \"NIL\")\n", ENOTTY);
    fprintf (out, "(cl:setf (get 'ENOTTY 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTTY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTTY)\n");
#ifdef ETXTBSY
    fprintf (out, "(cl:defconstant ETXTBSY %d \"NIL\")\n", ETXTBSY);
    fprintf (out, "(cl:setf (get 'ETXTBSY 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ETXTBSY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ETXTBSY)\n");
#ifdef EFBIG
    fprintf (out, "(cl:defconstant EFBIG %d \"NIL\")\n", EFBIG);
    fprintf (out, "(cl:setf (get 'EFBIG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EFBIG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EFBIG)\n");
#ifdef ENOSPC
    fprintf (out, "(cl:defconstant ENOSPC %d \"NIL\")\n", ENOSPC);
    fprintf (out, "(cl:setf (get 'ENOSPC 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOSPC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOSPC)\n");
#ifdef ESPIPE
    fprintf (out, "(cl:defconstant ESPIPE %d \"NIL\")\n", ESPIPE);
    fprintf (out, "(cl:setf (get 'ESPIPE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESPIPE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ESPIPE)\n");
#ifdef EROFS
    fprintf (out, "(cl:defconstant EROFS %d \"NIL\")\n", EROFS);
    fprintf (out, "(cl:setf (get 'EROFS 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EROFS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EROFS)\n");
#ifdef EMLINK
    fprintf (out, "(cl:defconstant EMLINK %d \"NIL\")\n", EMLINK);
    fprintf (out, "(cl:setf (get 'EMLINK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EMLINK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EMLINK)\n");
#ifdef EPIPE
    fprintf (out, "(cl:defconstant EPIPE %d \"NIL\")\n", EPIPE);
    fprintf (out, "(cl:setf (get 'EPIPE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPIPE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EPIPE)\n");
#ifdef EDOM
    fprintf (out, "(cl:defconstant EDOM %d \"NIL\")\n", EDOM);
    fprintf (out, "(cl:setf (get 'EDOM 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EDOM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EDOM)\n");
#ifdef ERANGE
    fprintf (out, "(cl:defconstant ERANGE %d \"NIL\")\n", ERANGE);
    fprintf (out, "(cl:setf (get 'ERANGE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ERANGE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ERANGE)\n");
#ifdef EDEADLK
    fprintf (out, "(cl:defconstant EDEADLK %d \"NIL\")\n", EDEADLK);
    fprintf (out, "(cl:setf (get 'EDEADLK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EDEADLK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EDEADLK)\n");
#ifdef ENAMETOOLONG
    fprintf (out, "(cl:defconstant ENAMETOOLONG %d \"NIL\")\n", ENAMETOOLONG);
    fprintf (out, "(cl:setf (get 'ENAMETOOLONG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENAMETOOLONG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENAMETOOLONG)\n");
#ifdef ENOLCK
    fprintf (out, "(cl:defconstant ENOLCK %d \"NIL\")\n", ENOLCK);
    fprintf (out, "(cl:setf (get 'ENOLCK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOLCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOLCK)\n");
#ifdef ENOSYS
    fprintf (out, "(cl:defconstant ENOSYS %d \"NIL\")\n", ENOSYS);
    fprintf (out, "(cl:setf (get 'ENOSYS 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOSYS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOSYS)\n");
#ifdef ENOTEMPTY
    fprintf (out, "(cl:defconstant ENOTEMPTY %d \"NIL\")\n", ENOTEMPTY);
    fprintf (out, "(cl:setf (get 'ENOTEMPTY 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTEMPTY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTEMPTY)\n");
#ifdef ELOOP
    fprintf (out, "(cl:defconstant ELOOP %d \"NIL\")\n", ELOOP);
    fprintf (out, "(cl:setf (get 'ELOOP 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ELOOP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ELOOP)\n");
#ifdef EWOULDBLOCK
    fprintf (out, "(cl:defconstant EWOULDBLOCK %d \"NIL\")\n", EWOULDBLOCK);
    fprintf (out, "(cl:setf (get 'EWOULDBLOCK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EWOULDBLOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EWOULDBLOCK)\n");
#ifdef ENOMSG
    fprintf (out, "(cl:defconstant ENOMSG %d \"NIL\")\n", ENOMSG);
    fprintf (out, "(cl:setf (get 'ENOMSG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOMSG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOMSG)\n");
#ifdef EIDRM
    fprintf (out, "(cl:defconstant EIDRM %d \"NIL\")\n", EIDRM);
    fprintf (out, "(cl:setf (get 'EIDRM 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EIDRM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EIDRM)\n");
#ifdef ECHRNG
    fprintf (out, "(cl:defconstant ECHRNG %d \"NIL\")\n", ECHRNG);
    fprintf (out, "(cl:setf (get 'ECHRNG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECHRNG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECHRNG)\n");
#ifdef EL2NSYNC
    fprintf (out, "(cl:defconstant EL2NSYNC %d \"NIL\")\n", EL2NSYNC);
    fprintf (out, "(cl:setf (get 'EL2NSYNC 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EL2NSYNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EL2NSYNC)\n");
#ifdef EL3HLT
    fprintf (out, "(cl:defconstant EL3HLT %d \"NIL\")\n", EL3HLT);
    fprintf (out, "(cl:setf (get 'EL3HLT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EL3HLT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EL3HLT)\n");
#ifdef EL3RST
    fprintf (out, "(cl:defconstant EL3RST %d \"NIL\")\n", EL3RST);
    fprintf (out, "(cl:setf (get 'EL3RST 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EL3RST (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EL3RST)\n");
#ifdef ELNRNG
    fprintf (out, "(cl:defconstant ELNRNG %d \"NIL\")\n", ELNRNG);
    fprintf (out, "(cl:setf (get 'ELNRNG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ELNRNG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ELNRNG)\n");
#ifdef EUNATCH
    fprintf (out, "(cl:defconstant EUNATCH %d \"NIL\")\n", EUNATCH);
    fprintf (out, "(cl:setf (get 'EUNATCH 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EUNATCH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EUNATCH)\n");
#ifdef ENOCSI
    fprintf (out, "(cl:defconstant ENOCSI %d \"NIL\")\n", ENOCSI);
    fprintf (out, "(cl:setf (get 'ENOCSI 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOCSI (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOCSI)\n");
#ifdef EL2HLT
    fprintf (out, "(cl:defconstant EL2HLT %d \"NIL\")\n", EL2HLT);
    fprintf (out, "(cl:setf (get 'EL2HLT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EL2HLT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EL2HLT)\n");
#ifdef EBADE
    fprintf (out, "(cl:defconstant EBADE %d \"NIL\")\n", EBADE);
    fprintf (out, "(cl:setf (get 'EBADE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBADE)\n");
#ifdef EBADR
    fprintf (out, "(cl:defconstant EBADR %d \"NIL\")\n", EBADR);
    fprintf (out, "(cl:setf (get 'EBADR 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBADR)\n");
#ifdef EXFULL
    fprintf (out, "(cl:defconstant EXFULL %d \"NIL\")\n", EXFULL);
    fprintf (out, "(cl:setf (get 'EXFULL 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EXFULL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EXFULL)\n");
#ifdef ENOANO
    fprintf (out, "(cl:defconstant ENOANO %d \"NIL\")\n", ENOANO);
    fprintf (out, "(cl:setf (get 'ENOANO 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOANO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOANO)\n");
#ifdef EBADRQC
    fprintf (out, "(cl:defconstant EBADRQC %d \"NIL\")\n", EBADRQC);
    fprintf (out, "(cl:setf (get 'EBADRQC 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADRQC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBADRQC)\n");
#ifdef EBADSLT
    fprintf (out, "(cl:defconstant EBADSLT %d \"NIL\")\n", EBADSLT);
    fprintf (out, "(cl:setf (get 'EBADSLT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADSLT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBADSLT)\n");
#ifdef EDEADLOCK
    fprintf (out, "(cl:defconstant EDEADLOCK %d \"NIL\")\n", EDEADLOCK);
    fprintf (out, "(cl:setf (get 'EDEADLOCK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EDEADLOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EDEADLOCK)\n");
#ifdef EBFONT
    fprintf (out, "(cl:defconstant EBFONT %d \"NIL\")\n", EBFONT);
    fprintf (out, "(cl:setf (get 'EBFONT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBFONT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBFONT)\n");
#ifdef ENOSTR
    fprintf (out, "(cl:defconstant ENOSTR %d \"NIL\")\n", ENOSTR);
    fprintf (out, "(cl:setf (get 'ENOSTR 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOSTR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOSTR)\n");
#ifdef ENODATA
    fprintf (out, "(cl:defconstant ENODATA %d \"NIL\")\n", ENODATA);
    fprintf (out, "(cl:setf (get 'ENODATA 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENODATA (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENODATA)\n");
#ifdef ETIME
    fprintf (out, "(cl:defconstant ETIME %d \"NIL\")\n", ETIME);
    fprintf (out, "(cl:setf (get 'ETIME 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ETIME (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ETIME)\n");
#ifdef ENOSR
    fprintf (out, "(cl:defconstant ENOSR %d \"NIL\")\n", ENOSR);
    fprintf (out, "(cl:setf (get 'ENOSR 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOSR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOSR)\n");
#ifdef ENONET
    fprintf (out, "(cl:defconstant ENONET %d \"NIL\")\n", ENONET);
    fprintf (out, "(cl:setf (get 'ENONET 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENONET (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENONET)\n");
#ifdef ENOPKG
    fprintf (out, "(cl:defconstant ENOPKG %d \"NIL\")\n", ENOPKG);
    fprintf (out, "(cl:setf (get 'ENOPKG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOPKG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOPKG)\n");
#ifdef EREMOTE
    fprintf (out, "(cl:defconstant EREMOTE %d \"NIL\")\n", EREMOTE);
    fprintf (out, "(cl:setf (get 'EREMOTE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EREMOTE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EREMOTE)\n");
#ifdef ENOLINK
    fprintf (out, "(cl:defconstant ENOLINK %d \"NIL\")\n", ENOLINK);
    fprintf (out, "(cl:setf (get 'ENOLINK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOLINK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOLINK)\n");
#ifdef EADV
    fprintf (out, "(cl:defconstant EADV %d \"NIL\")\n", EADV);
    fprintf (out, "(cl:setf (get 'EADV 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EADV (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EADV)\n");
#ifdef ESRMNT
    fprintf (out, "(cl:defconstant ESRMNT %d \"NIL\")\n", ESRMNT);
    fprintf (out, "(cl:setf (get 'ESRMNT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESRMNT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ESRMNT)\n");
#ifdef ECOMM
    fprintf (out, "(cl:defconstant ECOMM %d \"NIL\")\n", ECOMM);
    fprintf (out, "(cl:setf (get 'ECOMM 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECOMM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECOMM)\n");
#ifdef EPROTO
    fprintf (out, "(cl:defconstant EPROTO %d \"NIL\")\n", EPROTO);
    fprintf (out, "(cl:setf (get 'EPROTO 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPROTO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EPROTO)\n");
#ifdef EMULTIHOP
    fprintf (out, "(cl:defconstant EMULTIHOP %d \"NIL\")\n", EMULTIHOP);
    fprintf (out, "(cl:setf (get 'EMULTIHOP 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EMULTIHOP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EMULTIHOP)\n");
#ifdef EDOTDOT
    fprintf (out, "(cl:defconstant EDOTDOT %d \"NIL\")\n", EDOTDOT);
    fprintf (out, "(cl:setf (get 'EDOTDOT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EDOTDOT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EDOTDOT)\n");
#ifdef EBADMSG
    fprintf (out, "(cl:defconstant EBADMSG %d \"NIL\")\n", EBADMSG);
    fprintf (out, "(cl:setf (get 'EBADMSG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADMSG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBADMSG)\n");
#ifdef EOVERFLOW
    fprintf (out, "(cl:defconstant EOVERFLOW %d \"NIL\")\n", EOVERFLOW);
    fprintf (out, "(cl:setf (get 'EOVERFLOW 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EOVERFLOW (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EOVERFLOW)\n");
#ifdef ENOTUNIQ
    fprintf (out, "(cl:defconstant ENOTUNIQ %d \"NIL\")\n", ENOTUNIQ);
    fprintf (out, "(cl:setf (get 'ENOTUNIQ 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTUNIQ (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTUNIQ)\n");
#ifdef EBADFD
    fprintf (out, "(cl:defconstant EBADFD %d \"NIL\")\n", EBADFD);
    fprintf (out, "(cl:setf (get 'EBADFD 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADFD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EBADFD)\n");
#ifdef EREMCHG
    fprintf (out, "(cl:defconstant EREMCHG %d \"NIL\")\n", EREMCHG);
    fprintf (out, "(cl:setf (get 'EREMCHG 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EREMCHG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EREMCHG)\n");
#ifdef ELIBACC
    fprintf (out, "(cl:defconstant ELIBACC %d \"NIL\")\n", ELIBACC);
    fprintf (out, "(cl:setf (get 'ELIBACC 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ELIBACC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ELIBACC)\n");
#ifdef ELIBBAD
    fprintf (out, "(cl:defconstant ELIBBAD %d \"NIL\")\n", ELIBBAD);
    fprintf (out, "(cl:setf (get 'ELIBBAD 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ELIBBAD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ELIBBAD)\n");
#ifdef ELIBSCN
    fprintf (out, "(cl:defconstant ELIBSCN %d \"NIL\")\n", ELIBSCN);
    fprintf (out, "(cl:setf (get 'ELIBSCN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ELIBSCN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ELIBSCN)\n");
#ifdef ELIBMAX
    fprintf (out, "(cl:defconstant ELIBMAX %d \"NIL\")\n", ELIBMAX);
    fprintf (out, "(cl:setf (get 'ELIBMAX 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ELIBMAX (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ELIBMAX)\n");
#ifdef ELIBEXEC
    fprintf (out, "(cl:defconstant ELIBEXEC %d \"NIL\")\n", ELIBEXEC);
    fprintf (out, "(cl:setf (get 'ELIBEXEC 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ELIBEXEC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ELIBEXEC)\n");
#ifdef EILSEQ
    fprintf (out, "(cl:defconstant EILSEQ %d \"NIL\")\n", EILSEQ);
    fprintf (out, "(cl:setf (get 'EILSEQ 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EILSEQ (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EILSEQ)\n");
#ifdef ERESTART
    fprintf (out, "(cl:defconstant ERESTART %d \"NIL\")\n", ERESTART);
    fprintf (out, "(cl:setf (get 'ERESTART 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ERESTART (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ERESTART)\n");
#ifdef ESTRPIPE
    fprintf (out, "(cl:defconstant ESTRPIPE %d \"NIL\")\n", ESTRPIPE);
    fprintf (out, "(cl:setf (get 'ESTRPIPE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESTRPIPE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ESTRPIPE)\n");
#ifdef EUSERS
    fprintf (out, "(cl:defconstant EUSERS %d \"NIL\")\n", EUSERS);
    fprintf (out, "(cl:setf (get 'EUSERS 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EUSERS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EUSERS)\n");
#ifdef ENOTSOCK
    fprintf (out, "(cl:defconstant ENOTSOCK %d \"NIL\")\n", ENOTSOCK);
    fprintf (out, "(cl:setf (get 'ENOTSOCK 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTSOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTSOCK)\n");
#ifdef EDESTADDRREQ
    fprintf (out, "(cl:defconstant EDESTADDRREQ %d \"NIL\")\n", EDESTADDRREQ);
    fprintf (out, "(cl:setf (get 'EDESTADDRREQ 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EDESTADDRREQ (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EDESTADDRREQ)\n");
#ifdef EMSGSIZE
    fprintf (out, "(cl:defconstant EMSGSIZE %d \"NIL\")\n", EMSGSIZE);
    fprintf (out, "(cl:setf (get 'EMSGSIZE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EMSGSIZE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EMSGSIZE)\n");
#ifdef EPROTOTYPE
    fprintf (out, "(cl:defconstant EPROTOTYPE %d \"NIL\")\n", EPROTOTYPE);
    fprintf (out, "(cl:setf (get 'EPROTOTYPE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPROTOTYPE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EPROTOTYPE)\n");
#ifdef ENOPROTOOPT
    fprintf (out, "(cl:defconstant ENOPROTOOPT %d \"NIL\")\n", ENOPROTOOPT);
    fprintf (out, "(cl:setf (get 'ENOPROTOOPT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOPROTOOPT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOPROTOOPT)\n");
#ifdef EPROTONOSUPPORT
    fprintf (out, "(cl:defconstant EPROTONOSUPPORT %d \"NIL\")\n", EPROTONOSUPPORT);
    fprintf (out, "(cl:setf (get 'EPROTONOSUPPORT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPROTONOSUPPORT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EPROTONOSUPPORT)\n");
#ifdef ESOCKTNOSUPPORT
    fprintf (out, "(cl:defconstant ESOCKTNOSUPPORT %d \"NIL\")\n", ESOCKTNOSUPPORT);
    fprintf (out, "(cl:setf (get 'ESOCKTNOSUPPORT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESOCKTNOSUPPORT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ESOCKTNOSUPPORT)\n");
#ifdef EOPNOTSUPP
    fprintf (out, "(cl:defconstant EOPNOTSUPP %d \"NIL\")\n", EOPNOTSUPP);
    fprintf (out, "(cl:setf (get 'EOPNOTSUPP 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EOPNOTSUPP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EOPNOTSUPP)\n");
#ifdef EPFNOSUPPORT
    fprintf (out, "(cl:defconstant EPFNOSUPPORT %d \"NIL\")\n", EPFNOSUPPORT);
    fprintf (out, "(cl:setf (get 'EPFNOSUPPORT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPFNOSUPPORT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EPFNOSUPPORT)\n");
#ifdef EAFNOSUPPORT
    fprintf (out, "(cl:defconstant EAFNOSUPPORT %d \"NIL\")\n", EAFNOSUPPORT);
    fprintf (out, "(cl:setf (get 'EAFNOSUPPORT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAFNOSUPPORT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EAFNOSUPPORT)\n");
#ifdef EADDRINUSE
    fprintf (out, "(cl:defconstant EADDRINUSE %d \"NIL\")\n", EADDRINUSE);
    fprintf (out, "(cl:setf (get 'EADDRINUSE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EADDRINUSE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EADDRINUSE)\n");
#ifdef EADDRNOTAVAIL
    fprintf (out, "(cl:defconstant EADDRNOTAVAIL %d \"NIL\")\n", EADDRNOTAVAIL);
    fprintf (out, "(cl:setf (get 'EADDRNOTAVAIL 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EADDRNOTAVAIL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EADDRNOTAVAIL)\n");
#ifdef ENETDOWN
    fprintf (out, "(cl:defconstant ENETDOWN %d \"NIL\")\n", ENETDOWN);
    fprintf (out, "(cl:setf (get 'ENETDOWN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENETDOWN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENETDOWN)\n");
#ifdef ENETUNREACH
    fprintf (out, "(cl:defconstant ENETUNREACH %d \"NIL\")\n", ENETUNREACH);
    fprintf (out, "(cl:setf (get 'ENETUNREACH 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENETUNREACH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENETUNREACH)\n");
#ifdef ENETRESET
    fprintf (out, "(cl:defconstant ENETRESET %d \"NIL\")\n", ENETRESET);
    fprintf (out, "(cl:setf (get 'ENETRESET 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENETRESET (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENETRESET)\n");
#ifdef ECONNABORTED
    fprintf (out, "(cl:defconstant ECONNABORTED %d \"NIL\")\n", ECONNABORTED);
    fprintf (out, "(cl:setf (get 'ECONNABORTED 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECONNABORTED (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECONNABORTED)\n");
#ifdef ECONNRESET
    fprintf (out, "(cl:defconstant ECONNRESET %d \"NIL\")\n", ECONNRESET);
    fprintf (out, "(cl:setf (get 'ECONNRESET 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECONNRESET (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECONNRESET)\n");
#ifdef ENOBUFS
    fprintf (out, "(cl:defconstant ENOBUFS %d \"NIL\")\n", ENOBUFS);
    fprintf (out, "(cl:setf (get 'ENOBUFS 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOBUFS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOBUFS)\n");
#ifdef EISCONN
    fprintf (out, "(cl:defconstant EISCONN %d \"NIL\")\n", EISCONN);
    fprintf (out, "(cl:setf (get 'EISCONN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EISCONN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EISCONN)\n");
#ifdef ENOTCONN
    fprintf (out, "(cl:defconstant ENOTCONN %d \"NIL\")\n", ENOTCONN);
    fprintf (out, "(cl:setf (get 'ENOTCONN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTCONN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTCONN)\n");
#ifdef ESHUTDOWN
    fprintf (out, "(cl:defconstant ESHUTDOWN %d \"NIL\")\n", ESHUTDOWN);
    fprintf (out, "(cl:setf (get 'ESHUTDOWN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESHUTDOWN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ESHUTDOWN)\n");
#ifdef ETOOMANYREFS
    fprintf (out, "(cl:defconstant ETOOMANYREFS %d \"NIL\")\n", ETOOMANYREFS);
    fprintf (out, "(cl:setf (get 'ETOOMANYREFS 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ETOOMANYREFS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ETOOMANYREFS)\n");
#ifdef ETIMEDOUT
    fprintf (out, "(cl:defconstant ETIMEDOUT %d \"NIL\")\n", ETIMEDOUT);
    fprintf (out, "(cl:setf (get 'ETIMEDOUT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ETIMEDOUT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ETIMEDOUT)\n");
#ifdef ECONNREFUSED
    fprintf (out, "(cl:defconstant ECONNREFUSED %d \"NIL\")\n", ECONNREFUSED);
    fprintf (out, "(cl:setf (get 'ECONNREFUSED 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECONNREFUSED (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECONNREFUSED)\n");
#ifdef EHOSTDOWN
    fprintf (out, "(cl:defconstant EHOSTDOWN %d \"NIL\")\n", EHOSTDOWN);
    fprintf (out, "(cl:setf (get 'EHOSTDOWN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EHOSTDOWN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EHOSTDOWN)\n");
#ifdef EHOSTUNREACH
    fprintf (out, "(cl:defconstant EHOSTUNREACH %d \"NIL\")\n", EHOSTUNREACH);
    fprintf (out, "(cl:setf (get 'EHOSTUNREACH 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EHOSTUNREACH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EHOSTUNREACH)\n");
#ifdef EALREADY
    fprintf (out, "(cl:defconstant EALREADY %d \"NIL\")\n", EALREADY);
    fprintf (out, "(cl:setf (get 'EALREADY 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EALREADY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EALREADY)\n");
#ifdef EINPROGRESS
    fprintf (out, "(cl:defconstant EINPROGRESS %d \"NIL\")\n", EINPROGRESS);
    fprintf (out, "(cl:setf (get 'EINPROGRESS 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EINPROGRESS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EINPROGRESS)\n");
#ifdef ESTALE
    fprintf (out, "(cl:defconstant ESTALE %d \"NIL\")\n", ESTALE);
    fprintf (out, "(cl:setf (get 'ESTALE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESTALE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ESTALE)\n");
#ifdef EUCLEAN
    fprintf (out, "(cl:defconstant EUCLEAN %d \"NIL\")\n", EUCLEAN);
    fprintf (out, "(cl:setf (get 'EUCLEAN 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EUCLEAN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EUCLEAN)\n");
#ifdef ENOTNAM
    fprintf (out, "(cl:defconstant ENOTNAM %d \"NIL\")\n", ENOTNAM);
    fprintf (out, "(cl:setf (get 'ENOTNAM 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTNAM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOTNAM)\n");
#ifdef ENAVAIL
    fprintf (out, "(cl:defconstant ENAVAIL %d \"NIL\")\n", ENAVAIL);
    fprintf (out, "(cl:setf (get 'ENAVAIL 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENAVAIL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENAVAIL)\n");
#ifdef EREMOTEIO
    fprintf (out, "(cl:defconstant EREMOTEIO %d \"NIL\")\n", EREMOTEIO);
    fprintf (out, "(cl:setf (get 'EREMOTEIO 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EREMOTEIO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EREMOTEIO)\n");
#ifdef EDQUOT
    fprintf (out, "(cl:defconstant EDQUOT %d \"NIL\")\n", EDQUOT);
    fprintf (out, "(cl:setf (get 'EDQUOT 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EDQUOT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EDQUOT)\n");
#ifdef ENOMEDIUM
    fprintf (out, "(cl:defconstant ENOMEDIUM %d \"NIL\")\n", ENOMEDIUM);
    fprintf (out, "(cl:setf (get 'ENOMEDIUM 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOMEDIUM (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ENOMEDIUM)\n");
#ifdef EMEDIUMTYPE
    fprintf (out, "(cl:defconstant EMEDIUMTYPE %d \"NIL\")\n", EMEDIUMTYPE);
    fprintf (out, "(cl:setf (get 'EMEDIUMTYPE 'errno) t)\n");
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EMEDIUMTYPE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'EMEDIUMTYPE)\n");
#ifdef WNOHANG
    fprintf (out, "(cl:defconstant WNOHANG %d \"NIL\")\n", WNOHANG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for WNOHANG (unknown to the C compiler).\")\n");
#endif
#ifdef WUNTRACED
    fprintf (out, "(cl:defconstant WUNTRACED %d \"NIL\")\n", WUNTRACED);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for WUNTRACED (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type MODE-T (sb-alien:%ssigned %d)))\n", SIGNED_(mode_t), (8*sizeof(mode_t)));
#ifdef S_IFMT
    fprintf (out, "(cl:defconstant S-IFMT %d \"NIL\")\n", S_IFMT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFMT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFMT)\n");
#ifdef S_IFIFO
    fprintf (out, "(cl:defconstant S-IFIFO %d \"NIL\")\n", S_IFIFO);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFIFO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFIFO)\n");
#ifdef S_IFCHR
    fprintf (out, "(cl:defconstant S-IFCHR %d \"NIL\")\n", S_IFCHR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFCHR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFCHR)\n");
#ifdef S_IFDIR
    fprintf (out, "(cl:defconstant S-IFDIR %d \"NIL\")\n", S_IFDIR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFDIR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFDIR)\n");
#ifdef S_IFBLK
    fprintf (out, "(cl:defconstant S-IFBLK %d \"NIL\")\n", S_IFBLK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFBLK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFBLK)\n");
#ifdef S_IFREG
    fprintf (out, "(cl:defconstant S-IFREG %d \"NIL\")\n", S_IFREG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFREG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFREG)\n");
#ifdef S_IFLNK
    fprintf (out, "(cl:defconstant S-IFLNK %d \"NIL\")\n", S_IFLNK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFLNK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFLNK)\n");
#ifdef S_IFSOCK
    fprintf (out, "(cl:defconstant S-IFSOCK %d \"NIL\")\n", S_IFSOCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFSOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFSOCK)\n");
#ifdef S_IFWHT
    fprintf (out, "(cl:defconstant S-IFWHT %d \"NIL\")\n", S_IFWHT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IFWHT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IFWHT)\n");
#ifdef S_ISUID
    fprintf (out, "(cl:defconstant S-ISUID %d \"NIL\")\n", S_ISUID);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_ISUID (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-ISUID)\n");
#ifdef S_ISGID
    fprintf (out, "(cl:defconstant S-ISGID %d \"NIL\")\n", S_ISGID);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_ISGID (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-ISGID)\n");
#ifdef S_ISVTX
    fprintf (out, "(cl:defconstant S-ISVTX %d \"NIL\")\n", S_ISVTX);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_ISVTX (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-ISVTX)\n");
#ifdef S_IRUSR
    fprintf (out, "(cl:defconstant S-IRUSR %d \"NIL\")\n", S_IRUSR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IRUSR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IRUSR)\n");
#ifdef S_IWUSR
    fprintf (out, "(cl:defconstant S-IWUSR %d \"NIL\")\n", S_IWUSR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IWUSR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IWUSR)\n");
#ifdef S_IXUSR
    fprintf (out, "(cl:defconstant S-IXUSR %d \"NIL\")\n", S_IXUSR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IXUSR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IXUSR)\n");
#ifdef S_IRUSR
    fprintf (out, "(cl:defconstant S-IREAD %d \"NIL\")\n", S_IRUSR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IRUSR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IREAD)\n");
#ifdef S_IWUSR
    fprintf (out, "(cl:defconstant S-IWRITE %d \"NIL\")\n", S_IWUSR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IWUSR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IWRITE)\n");
#ifdef S_IXUSR
    fprintf (out, "(cl:defconstant S-IEXEC %d \"NIL\")\n", S_IXUSR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IXUSR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IEXEC)\n");
#ifdef S_IRGRP
    fprintf (out, "(cl:defconstant S-IRGRP %d \"NIL\")\n", S_IRGRP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IRGRP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IRGRP)\n");
#ifdef S_IWGRP
    fprintf (out, "(cl:defconstant S-IWGRP %d \"NIL\")\n", S_IWGRP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IWGRP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IWGRP)\n");
#ifdef S_IXGRP
    fprintf (out, "(cl:defconstant S-IXGRP %d \"NIL\")\n", S_IXGRP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IXGRP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IXGRP)\n");
#ifdef S_IROTH
    fprintf (out, "(cl:defconstant S-IROTH %d \"NIL\")\n", S_IROTH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IROTH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IROTH)\n");
#ifdef S_IWOTH
    fprintf (out, "(cl:defconstant S-IWOTH %d \"NIL\")\n", S_IWOTH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IWOTH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IWOTH)\n");
#ifdef S_IXOTH
    fprintf (out, "(cl:defconstant S-IXOTH %d \"NIL\")\n", S_IXOTH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for S_IXOTH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'S-IXOTH)\n");
#ifdef R_OK
    fprintf (out, "(cl:defconstant R-OK %d \"NIL\")\n", R_OK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for R_OK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'R-OK)\n");
#ifdef W_OK
    fprintf (out, "(cl:defconstant W-OK %d \"NIL\")\n", W_OK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for W_OK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'W-OK)\n");
#ifdef X_OK
    fprintf (out, "(cl:defconstant X-OK %d \"NIL\")\n", X_OK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for X_OK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'X-OK)\n");
#ifdef F_OK
    fprintf (out, "(cl:defconstant F-OK %d \"NIL\")\n", F_OK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_OK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-OK)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type OFF-T (sb-alien:%ssigned %d)))\n", SIGNED_(off_t), (8*sizeof(off_t)));
#ifdef PROT_NONE
    fprintf (out, "(cl:defconstant PROT-NONE %d \"mmap: no protection\")\n", PROT_NONE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for PROT_NONE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'PROT-NONE)\n");
#ifdef PROT_READ
    fprintf (out, "(cl:defconstant PROT-READ %d \"mmap: read protection\")\n", PROT_READ);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for PROT_READ (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'PROT-READ)\n");
#ifdef PROT_WRITE
    fprintf (out, "(cl:defconstant PROT-WRITE %d \"mmap: write protection\")\n", PROT_WRITE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for PROT_WRITE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'PROT-WRITE)\n");
#ifdef PROT_EXEC
    fprintf (out, "(cl:defconstant PROT-EXEC %d \"mmap: execute protection\")\n", PROT_EXEC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for PROT_EXEC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'PROT-EXEC)\n");
#ifdef MAP_SHARED
    fprintf (out, "(cl:defconstant MAP-SHARED %d \"mmap: shared memory\")\n", MAP_SHARED);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MAP_SHARED (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MAP-SHARED)\n");
#ifdef MAP_PRIVATE
    fprintf (out, "(cl:defconstant MAP-PRIVATE %d \"mmap: private mapping\")\n", MAP_PRIVATE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MAP_PRIVATE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MAP-PRIVATE)\n");
#ifdef MAP_FIXED
    fprintf (out, "(cl:defconstant MAP-FIXED %d \"mmap: map at given location\")\n", MAP_FIXED);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MAP_FIXED (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MAP-FIXED)\n");
#ifdef MS_ASYNC
    fprintf (out, "(cl:defconstant MS-ASYNC %d \"msync: return immediately\")\n", MS_ASYNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MS_ASYNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MS-ASYNC)\n");
#ifdef MS_SYNC
    fprintf (out, "(cl:defconstant MS-SYNC %d \"msync: perform synchronous writes\")\n", MS_SYNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MS_SYNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MS-SYNC)\n");
#ifdef MS_INVALIDATE
    fprintf (out, "(cl:defconstant MS-INVALIDATE %d \"msync: invalidate all cached data\")\n", MS_INVALIDATE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MS_INVALIDATE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MS-INVALIDATE)\n");
#ifdef MCL_CURRENT
    fprintf (out, "(cl:defconstant MCL-CURRENT %d \"mlockall: lock all pages which are currently mapped into the address space of the process.\")\n", MCL_CURRENT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MCL_CURRENT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MCL-CURRENT)\n");
#ifdef MCL_FUTURE
    fprintf (out, "(cl:defconstant MCL-FUTURE %d \"mlockall: lock all pages which will become mapped into the address space of the process in the future.\")\n", MCL_FUTURE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MCL_FUTURE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'MCL-FUTURE)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct DIRENT %d\n", sizeof(struct dirent64));
    fprintf (out, " (INO INO-T \"ino_t\"\n");
{ struct dirent64 t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.d_ino)) - ((unsigned long)&(t)));
}
{ struct dirent64 t;
    fprintf (out, "  %d)\n", sizeof(t.d_ino));
}
    fprintf (out, " (NAME C-STRING \"char *\"\n");
{ struct dirent64 t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.d_name)) - ((unsigned long)&(t)));
}
{ struct dirent64 t;
    fprintf (out, "  %d)\n", sizeof(t.d_name));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ALIEN-PASSWD %d\n", sizeof(struct passwd));
    fprintf (out, " (NAME C-STRING-POINTER \"char *\"\n");
{ struct passwd t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.pw_name)) - ((unsigned long)&(t)));
}
{ struct passwd t;
    fprintf (out, "  %d)\n", sizeof(t.pw_name));
}
    fprintf (out, " (PASSWD C-STRING-POINTER \"char *\"\n");
{ struct passwd t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.pw_passwd)) - ((unsigned long)&(t)));
}
{ struct passwd t;
    fprintf (out, "  %d)\n", sizeof(t.pw_passwd));
}
    fprintf (out, " (UID UID-T \"uid_t\"\n");
{ struct passwd t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.pw_uid)) - ((unsigned long)&(t)));
}
{ struct passwd t;
    fprintf (out, "  %d)\n", sizeof(t.pw_uid));
}
    fprintf (out, " (GID GID-T \"gid_t\"\n");
{ struct passwd t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.pw_gid)) - ((unsigned long)&(t)));
}
{ struct passwd t;
    fprintf (out, "  %d)\n", sizeof(t.pw_gid));
}
    fprintf (out, " (GECOS C-STRING-POINTER \"char *\"\n");
{ struct passwd t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.pw_gecos)) - ((unsigned long)&(t)));
}
{ struct passwd t;
    fprintf (out, "  %d)\n", sizeof(t.pw_gecos));
}
    fprintf (out, " (DIR C-STRING-POINTER \"char *\"\n");
{ struct passwd t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.pw_dir)) - ((unsigned long)&(t)));
}
{ struct passwd t;
    fprintf (out, "  %d)\n", sizeof(t.pw_dir));
}
    fprintf (out, " (SHELL C-STRING-POINTER \"char *\"\n");
{ struct passwd t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.pw_shell)) - ((unsigned long)&(t)));
}
{ struct passwd t;
    fprintf (out, "  %d)\n", sizeof(t.pw_shell));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ALIEN-GROUP %d\n", sizeof(struct group));
    fprintf (out, " (NAME C-STRING-POINTER \"char *\"\n");
{ struct group t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.gr_name)) - ((unsigned long)&(t)));
}
{ struct group t;
    fprintf (out, "  %d)\n", sizeof(t.gr_name));
}
    fprintf (out, " (PASSWD C-STRING-POINTER \"char *\"\n");
{ struct group t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.gr_passwd)) - ((unsigned long)&(t)));
}
{ struct group t;
    fprintf (out, "  %d)\n", sizeof(t.gr_passwd));
}
    fprintf (out, " (GID GID-T \"gid_t\"\n");
{ struct group t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.gr_gid)) - ((unsigned long)&(t)));
}
{ struct group t;
    fprintf (out, "  %d)\n", sizeof(t.gr_gid));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ALIEN-STAT %d\n", sizeof(struct stat));
    fprintf (out, " (MODE MODE-T \"mode_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_mode)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_mode));
}
    fprintf (out, " (INO INO-T \"ino_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_ino)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_ino));
}
    fprintf (out, " (DEV DEV-T \"dev_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_dev)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_dev));
}
    fprintf (out, " (NLINK NLINK-T \"nlink_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_nlink)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_nlink));
}
    fprintf (out, " (UID UID-T \"uid_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_uid)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_uid));
}
    fprintf (out, " (GID GID-T \"gid_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_gid)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_gid));
}
    fprintf (out, " (SIZE OFF-T \"off_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_size)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_size));
}
    fprintf (out, " (ATIME TIME-T \"time_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_atime)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_atime));
}
    fprintf (out, " (MTIME TIME-T \"time_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_mtime)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_mtime));
}
    fprintf (out, " (CTIME TIME-T \"time_t\"\n");
{ struct stat t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.st_ctime)) - ((unsigned long)&(t)));
}
{ struct stat t;
    fprintf (out, "  %d)\n", sizeof(t.st_ctime));
}
    fprintf (out, "))\n");
#ifdef O_RDONLY
    fprintf (out, "(cl:defconstant O-RDONLY %d \"NIL\")\n", O_RDONLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_RDONLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-RDONLY)\n");
#ifdef O_WRONLY
    fprintf (out, "(cl:defconstant O-WRONLY %d \"NIL\")\n", O_WRONLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_WRONLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-WRONLY)\n");
#ifdef O_RDWR
    fprintf (out, "(cl:defconstant O-RDWR %d \"NIL\")\n", O_RDWR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_RDWR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-RDWR)\n");
#ifdef O_CREAT
    fprintf (out, "(cl:defconstant O-CREAT %d \"NIL\")\n", O_CREAT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_CREAT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-CREAT)\n");
#ifdef O_EXCL
    fprintf (out, "(cl:defconstant O-EXCL %d \"NIL\")\n", O_EXCL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_EXCL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-EXCL)\n");
#ifdef O_NOCTTY
    fprintf (out, "(cl:defconstant O-NOCTTY %d \"NIL\")\n", O_NOCTTY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_NOCTTY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-NOCTTY)\n");
#ifdef O_TRUNC
    fprintf (out, "(cl:defconstant O-TRUNC %d \"NIL\")\n", O_TRUNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_TRUNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-TRUNC)\n");
#ifdef O_APPEND
    fprintf (out, "(cl:defconstant O-APPEND %d \"NIL\")\n", O_APPEND);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_APPEND (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-APPEND)\n");
#ifdef O_NONBLOCK
    fprintf (out, "(cl:defconstant O-NONBLOCK %d \"NIL\")\n", O_NONBLOCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_NONBLOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-NONBLOCK)\n");
#ifdef O_NDELAY
    fprintf (out, "(cl:defconstant O-NDELAY %d \"NIL\")\n", O_NDELAY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_NDELAY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-NDELAY)\n");
#ifdef O_SYNC
    fprintf (out, "(cl:defconstant O-SYNC %d \"NIL\")\n", O_SYNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_SYNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-SYNC)\n");
#ifdef O_NOFOLLOW
    fprintf (out, "(cl:defconstant O-NOFOLLOW %d \"NIL\")\n", O_NOFOLLOW);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_NOFOLLOW (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-NOFOLLOW)\n");
#ifdef O_DIRECTORY
    fprintf (out, "(cl:defconstant O-DIRECTORY %d \"NIL\")\n", O_DIRECTORY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_DIRECTORY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-DIRECTORY)\n");
#ifdef O_DIRECT
    fprintf (out, "(cl:defconstant O-DIRECT %d \"NIL\")\n", O_DIRECT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_DIRECT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-DIRECT)\n");
#ifdef O_ASYNC
    fprintf (out, "(cl:defconstant O-ASYNC %d \"NIL\")\n", O_ASYNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_ASYNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-ASYNC)\n");
#ifdef O_LARGEFILE
    fprintf (out, "(cl:defconstant O-LARGEFILE %d \"NIL\")\n", O_LARGEFILE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_LARGEFILE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-LARGEFILE)\n");
#ifdef O_DSYNC
    fprintf (out, "(cl:defconstant O-DSYNC %d \"NIL\")\n", O_DSYNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_DSYNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-DSYNC)\n");
#ifdef O_RSYNC
    fprintf (out, "(cl:defconstant O-RSYNC %d \"NIL\")\n", O_RSYNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_RSYNC (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'O-RSYNC)\n");
#ifdef SEEK_SET
    fprintf (out, "(cl:defconstant SEEK-SET %d \"NIL\")\n", SEEK_SET);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SEEK_SET (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SEEK-SET)\n");
#ifdef SEEK_CUR
    fprintf (out, "(cl:defconstant SEEK-CUR %d \"NIL\")\n", SEEK_CUR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SEEK_CUR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SEEK-CUR)\n");
#ifdef SEEK_END
    fprintf (out, "(cl:defconstant SEEK-END %d \"NIL\")\n", SEEK_END);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SEEK_END (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'SEEK-END)\n");
#ifdef F_DUPFD
    fprintf (out, "(cl:defconstant F-DUPFD %d \"NIL\")\n", F_DUPFD);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_DUPFD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-DUPFD)\n");
#ifdef F_GETFD
    fprintf (out, "(cl:defconstant F-GETFD %d \"NIL\")\n", F_GETFD);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_GETFD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-GETFD)\n");
#ifdef F_SETFD
    fprintf (out, "(cl:defconstant F-SETFD %d \"NIL\")\n", F_SETFD);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_SETFD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-SETFD)\n");
#ifdef F_GETFL
    fprintf (out, "(cl:defconstant F-GETFL %d \"NIL\")\n", F_GETFL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_GETFL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-GETFL)\n");
#ifdef F_SETFL
    fprintf (out, "(cl:defconstant F-SETFL %d \"NIL\")\n", F_SETFL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_SETFL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-SETFL)\n");
#ifdef F_GETLK
    fprintf (out, "(cl:defconstant F-GETLK %d \"NIL\")\n", F_GETLK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_GETLK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-GETLK)\n");
#ifdef F_SETLK
    fprintf (out, "(cl:defconstant F-SETLK %d \"NIL\")\n", F_SETLK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_SETLK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-SETLK)\n");
#ifdef F_SETLKW
    fprintf (out, "(cl:defconstant F-SETLKW %d \"NIL\")\n", F_SETLKW);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_SETLKW (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-SETLKW)\n");
#ifdef F_GETOWN
    fprintf (out, "(cl:defconstant F-GETOWN %d \"NIL\")\n", F_GETOWN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_GETOWN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-GETOWN)\n");
#ifdef F_SETOWN
    fprintf (out, "(cl:defconstant F-SETOWN %d \"NIL\")\n", F_SETOWN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_SETOWN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-SETOWN)\n");
#ifdef F_RDLCK
    fprintf (out, "(cl:defconstant F-RDLCK %d \"NIL\")\n", F_RDLCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_RDLCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-RDLCK)\n");
#ifdef F_WRLCK
    fprintf (out, "(cl:defconstant F-WRLCK %d \"NIL\")\n", F_WRLCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_WRLCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-WRLCK)\n");
#ifdef F_UNLCK
    fprintf (out, "(cl:defconstant F-UNLCK %d \"NIL\")\n", F_UNLCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_UNLCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-UNLCK)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ALIEN-FLOCK %d\n", sizeof(struct flock));
    fprintf (out, " (TYPE SHORT \"short\"\n");
{ struct flock t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.l_type)) - ((unsigned long)&(t)));
}
{ struct flock t;
    fprintf (out, "  %d)\n", sizeof(t.l_type));
}
    fprintf (out, " (WHENCE SHORT \"short\"\n");
{ struct flock t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.l_whence)) - ((unsigned long)&(t)));
}
{ struct flock t;
    fprintf (out, "  %d)\n", sizeof(t.l_whence));
}
    fprintf (out, " (START OFF-T \"off_t\"\n");
{ struct flock t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.l_start)) - ((unsigned long)&(t)));
}
{ struct flock t;
    fprintf (out, "  %d)\n", sizeof(t.l_start));
}
    fprintf (out, " (LEN OFF-T \"off_t\"\n");
{ struct flock t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.l_len)) - ((unsigned long)&(t)));
}
{ struct flock t;
    fprintf (out, "  %d)\n", sizeof(t.l_len));
}
    fprintf (out, " (PID PID-T \"pid_t\"\n");
{ struct flock t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.l_pid)) - ((unsigned long)&(t)));
}
{ struct flock t;
    fprintf (out, "  %d)\n", sizeof(t.l_pid));
}
    fprintf (out, "))\n");
#ifdef F_LOCK
    fprintf (out, "(cl:defconstant F-LOCK %d \"NIL\")\n", F_LOCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_LOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-LOCK)\n");
#ifdef F_TLOCK
    fprintf (out, "(cl:defconstant F-TLOCK %d \"NIL\")\n", F_TLOCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_TLOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-TLOCK)\n");
#ifdef F_ULOCK
    fprintf (out, "(cl:defconstant F-ULOCK %d \"NIL\")\n", F_ULOCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_ULOCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-ULOCK)\n");
#ifdef F_TEST
    fprintf (out, "(cl:defconstant F-TEST %d \"NIL\")\n", F_TEST);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_TEST (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'F-TEST)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type CC-T (sb-alien:%ssigned %d)))\n", SIGNED_(cc_t), (8*sizeof(cc_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type SPEED-T (sb-alien:%ssigned %d)))\n", SIGNED_(speed_t), (8*sizeof(speed_t)));
    fprintf (out, "(cl:export 'SPEED-T)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type TCFLAG-T (sb-alien:%ssigned %d)))\n", SIGNED_(tcflag_t), (8*sizeof(tcflag_t)));
    fprintf (out, "(cl:export 'TCFLAG-T)\n");
#ifdef NCCS
    fprintf (out, "(cl:defconstant NCCS %d \"NIL\")\n", NCCS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NCCS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'NCCS)\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ALIEN-TERMIOS %d\n", sizeof(struct termios));
    fprintf (out, " (IFLAG TCFLAG-T \"tcflag_t\"\n");
{ struct termios t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.c_iflag)) - ((unsigned long)&(t)));
}
{ struct termios t;
    fprintf (out, "  %d)\n", sizeof(t.c_iflag));
}
    fprintf (out, " (OFLAG TCFLAG-T \"tcflag_t\"\n");
{ struct termios t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.c_oflag)) - ((unsigned long)&(t)));
}
{ struct termios t;
    fprintf (out, "  %d)\n", sizeof(t.c_oflag));
}
    fprintf (out, " (CFLAG TCFLAG-T \"tcflag_t\"\n");
{ struct termios t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.c_cflag)) - ((unsigned long)&(t)));
}
{ struct termios t;
    fprintf (out, "  %d)\n", sizeof(t.c_cflag));
}
    fprintf (out, " (LFLAG TCFLAG-T \"tcflag_t\"\n");
{ struct termios t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.c_lflag)) - ((unsigned long)&(t)));
}
{ struct termios t;
    fprintf (out, "  %d)\n", sizeof(t.c_lflag));
}
    fprintf (out, " (CC (ARRAY CC-T) \"cc_t\"\n");
{ struct termios t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.c_cc)) - ((unsigned long)&(t)));
}
{ struct termios t;
    fprintf (out, "  %d)\n", sizeof(t.c_cc));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type SUSECONDS-T (sb-alien:%ssigned %d)))\n", SIGNED_(suseconds_t), (8*sizeof(suseconds_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ALIEN-UTIMBUF %d\n", sizeof(struct utimbuf));
    fprintf (out, " (ACTIME TIME-T \"time_t\"\n");
{ struct utimbuf t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.actime)) - ((unsigned long)&(t)));
}
{ struct utimbuf t;
    fprintf (out, "  %d)\n", sizeof(t.actime));
}
    fprintf (out, " (MODTIME TIME-T \"time_t\"\n");
{ struct utimbuf t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.modtime)) - ((unsigned long)&(t)));
}
{ struct utimbuf t;
    fprintf (out, "  %d)\n", sizeof(t.modtime));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ALIEN-TIMEVAL %d\n", sizeof(struct timeval));
    fprintf (out, " (SEC TIME-T \"time_t\"\n");
{ struct timeval t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.tv_sec)) - ((unsigned long)&(t)));
}
{ struct timeval t;
    fprintf (out, "  %d)\n", sizeof(t.tv_sec));
}
    fprintf (out, " (USEC SUSECONDS-T \"suseconds_t\"\n");
{ struct timeval t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.tv_usec)) - ((unsigned long)&(t)));
}
{ struct timeval t;
    fprintf (out, "  %d)\n", sizeof(t.tv_usec));
}
    fprintf (out, "))\n");
#ifdef VEOF
    fprintf (out, "(cl:defconstant VEOF %d \"NIL\")\n", VEOF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VEOF (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VEOF)\n");
#ifdef VEOL
    fprintf (out, "(cl:defconstant VEOL %d \"NIL\")\n", VEOL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VEOL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VEOL)\n");
#ifdef VERASE
    fprintf (out, "(cl:defconstant VERASE %d \"NIL\")\n", VERASE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VERASE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VERASE)\n");
#ifdef VINTR
    fprintf (out, "(cl:defconstant VINTR %d \"NIL\")\n", VINTR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VINTR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VINTR)\n");
#ifdef VKILL
    fprintf (out, "(cl:defconstant VKILL %d \"NIL\")\n", VKILL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VKILL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VKILL)\n");
#ifdef VMIN
    fprintf (out, "(cl:defconstant VMIN %d \"NIL\")\n", VMIN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VMIN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VMIN)\n");
#ifdef VQUIT
    fprintf (out, "(cl:defconstant VQUIT %d \"NIL\")\n", VQUIT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VQUIT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VQUIT)\n");
#ifdef VSTART
    fprintf (out, "(cl:defconstant VSTART %d \"NIL\")\n", VSTART);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VSTART (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VSTART)\n");
#ifdef VSTOP
    fprintf (out, "(cl:defconstant VSTOP %d \"NIL\")\n", VSTOP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VSTOP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VSTOP)\n");
#ifdef VSUSP
    fprintf (out, "(cl:defconstant VSUSP %d \"NIL\")\n", VSUSP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VSUSP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VSUSP)\n");
#ifdef VTIME
    fprintf (out, "(cl:defconstant VTIME %d \"NIL\")\n", VTIME);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VTIME (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VTIME)\n");
#ifdef _POSIX_VDISABLE
    fprintf (out, "(cl:defconstant VDISABLE %d \"NIL\")\n", _POSIX_VDISABLE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for _POSIX_VDISABLE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VDISABLE)\n");
#ifdef BRKINT
    fprintf (out, "(cl:defconstant BRKINT %d \"NIL\")\n", BRKINT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for BRKINT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'BRKINT)\n");
#ifdef ICRNL
    fprintf (out, "(cl:defconstant ICRNL %d \"NIL\")\n", ICRNL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ICRNL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ICRNL)\n");
#ifdef IGNBRK
    fprintf (out, "(cl:defconstant IGNBRK %d \"NIL\")\n", IGNBRK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for IGNBRK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'IGNBRK)\n");
#ifdef IGNCR
    fprintf (out, "(cl:defconstant IGNCR %d \"NIL\")\n", IGNCR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for IGNCR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'IGNCR)\n");
#ifdef IGNPAR
    fprintf (out, "(cl:defconstant IGNPAR %d \"NIL\")\n", IGNPAR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for IGNPAR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'IGNPAR)\n");
#ifdef INLCR
    fprintf (out, "(cl:defconstant INLCR %d \"NIL\")\n", INLCR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for INLCR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'INLCR)\n");
#ifdef INPCK
    fprintf (out, "(cl:defconstant INPCK %d \"NIL\")\n", INPCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for INPCK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'INPCK)\n");
#ifdef ISTRIP
    fprintf (out, "(cl:defconstant ISTRIP %d \"NIL\")\n", ISTRIP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ISTRIP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ISTRIP)\n");
#ifdef IXOFF
    fprintf (out, "(cl:defconstant IXOFF %d \"NIL\")\n", IXOFF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for IXOFF (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'IXOFF)\n");
#ifdef IXON
    fprintf (out, "(cl:defconstant IXON %d \"NIL\")\n", IXON);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for IXON (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'IXON)\n");
#ifdef PARMRK
    fprintf (out, "(cl:defconstant PARMRK %d \"NIL\")\n", PARMRK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for PARMRK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'PARMRK)\n");
#ifdef OPOST
    fprintf (out, "(cl:defconstant OPOST %d \"NIL\")\n", OPOST);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for OPOST (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'OPOST)\n");
#ifdef OCRNL
    fprintf (out, "(cl:defconstant OCRNL %d \"NIL\")\n", OCRNL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for OCRNL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'OCRNL)\n");
#ifdef ONOCR
    fprintf (out, "(cl:defconstant ONOCR %d \"NIL\")\n", ONOCR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ONOCR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ONOCR)\n");
#ifdef ONLRET
    fprintf (out, "(cl:defconstant ONLRET %d \"NIL\")\n", ONLRET);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ONLRET (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ONLRET)\n");
#ifdef OFDEL
    fprintf (out, "(cl:defconstant OFDEL %d \"NIL\")\n", OFDEL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for OFDEL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'OFDEL)\n");
#ifdef OFILL
    fprintf (out, "(cl:defconstant OFILL %d \"NIL\")\n", OFILL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for OFILL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'OFILL)\n");
#ifdef NLDLY
    fprintf (out, "(cl:defconstant NLDLY %d \"NIL\")\n", NLDLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NLDLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'NLDLY)\n");
#ifdef NL0
    fprintf (out, "(cl:defconstant NL0 %d \"NIL\")\n", NL0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NL0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'NL0)\n");
#ifdef NL1
    fprintf (out, "(cl:defconstant NL1 %d \"NIL\")\n", NL1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NL1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'NL1)\n");
#ifdef CRDLY
    fprintf (out, "(cl:defconstant CRDLY %d \"NIL\")\n", CRDLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CRDLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CRDLY)\n");
#ifdef CR0
    fprintf (out, "(cl:defconstant CR0 %d \"NIL\")\n", CR0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CR0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CR0)\n");
#ifdef CR1
    fprintf (out, "(cl:defconstant CR1 %d \"NIL\")\n", CR1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CR1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CR1)\n");
#ifdef CR2
    fprintf (out, "(cl:defconstant CR2 %d \"NIL\")\n", CR2);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CR2 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CR2)\n");
#ifdef CR3
    fprintf (out, "(cl:defconstant CR3 %d \"NIL\")\n", CR3);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CR3 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CR3)\n");
#ifdef TABDLY
    fprintf (out, "(cl:defconstant TABDLY %d \"NIL\")\n", TABDLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TABDLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TABDLY)\n");
#ifdef TAB0
    fprintf (out, "(cl:defconstant TAB0 %d \"NIL\")\n", TAB0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TAB0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TAB0)\n");
#ifdef TAB1
    fprintf (out, "(cl:defconstant TAB1 %d \"NIL\")\n", TAB1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TAB1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TAB1)\n");
#ifdef TAB2
    fprintf (out, "(cl:defconstant TAB2 %d \"NIL\")\n", TAB2);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TAB2 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TAB2)\n");
#ifdef TAB3
    fprintf (out, "(cl:defconstant TAB3 %d \"NIL\")\n", TAB3);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TAB3 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TAB3)\n");
#ifdef BSDLY
    fprintf (out, "(cl:defconstant BSDLY %d \"NIL\")\n", BSDLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for BSDLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'BSDLY)\n");
#ifdef BS0
    fprintf (out, "(cl:defconstant BS0 %d \"NIL\")\n", BS0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for BS0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'BS0)\n");
#ifdef BS1
    fprintf (out, "(cl:defconstant BS1 %d \"NIL\")\n", BS1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for BS1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'BS1)\n");
#ifdef VTDLY
    fprintf (out, "(cl:defconstant VTDLY %d \"NIL\")\n", VTDLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VTDLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VTDLY)\n");
#ifdef VT0
    fprintf (out, "(cl:defconstant VT0 %d \"NIL\")\n", VT0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VT0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VT0)\n");
#ifdef VT1
    fprintf (out, "(cl:defconstant VT1 %d \"NIL\")\n", VT1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for VT1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'VT1)\n");
#ifdef FFDLY
    fprintf (out, "(cl:defconstant FFDLY %d \"NIL\")\n", FFDLY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for FFDLY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'FFDLY)\n");
#ifdef FF0
    fprintf (out, "(cl:defconstant FF0 %d \"NIL\")\n", FF0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for FF0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'FF0)\n");
#ifdef FF1
    fprintf (out, "(cl:defconstant FF1 %d \"NIL\")\n", FF1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for FF1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'FF1)\n");
#ifdef B0
    fprintf (out, "(cl:defconstant B0 %d \"NIL\")\n", B0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B0)\n");
#ifdef B50
    fprintf (out, "(cl:defconstant B50 %d \"NIL\")\n", B50);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B50 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B50)\n");
#ifdef B75
    fprintf (out, "(cl:defconstant B75 %d \"NIL\")\n", B75);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B75 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B75)\n");
#ifdef B110
    fprintf (out, "(cl:defconstant B110 %d \"NIL\")\n", B110);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B110 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B110)\n");
#ifdef B134
    fprintf (out, "(cl:defconstant B134 %d \"NIL\")\n", B134);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B134 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B134)\n");
#ifdef B150
    fprintf (out, "(cl:defconstant B150 %d \"NIL\")\n", B150);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B150 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B150)\n");
#ifdef B200
    fprintf (out, "(cl:defconstant B200 %d \"NIL\")\n", B200);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B200 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B200)\n");
#ifdef B300
    fprintf (out, "(cl:defconstant B300 %d \"NIL\")\n", B300);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B300 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B300)\n");
#ifdef B600
    fprintf (out, "(cl:defconstant B600 %d \"NIL\")\n", B600);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B600 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B600)\n");
#ifdef B1200
    fprintf (out, "(cl:defconstant B1200 %d \"NIL\")\n", B1200);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B1200 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B1200)\n");
#ifdef B1800
    fprintf (out, "(cl:defconstant B1800 %d \"NIL\")\n", B1800);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B1800 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B1800)\n");
#ifdef B2400
    fprintf (out, "(cl:defconstant B2400 %d \"NIL\")\n", B2400);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B2400 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B2400)\n");
#ifdef B4800
    fprintf (out, "(cl:defconstant B4800 %d \"NIL\")\n", B4800);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B4800 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B4800)\n");
#ifdef B9600
    fprintf (out, "(cl:defconstant B9600 %d \"NIL\")\n", B9600);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B9600 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B9600)\n");
#ifdef B19200
    fprintf (out, "(cl:defconstant B19200 %d \"NIL\")\n", B19200);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B19200 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B19200)\n");
#ifdef B38400
    fprintf (out, "(cl:defconstant B38400 %d \"NIL\")\n", B38400);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B38400 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B38400)\n");
#ifdef B57600
    fprintf (out, "(cl:defconstant B57600 %d \"NIL\")\n", B57600);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B57600 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B57600)\n");
#ifdef B115200
    fprintf (out, "(cl:defconstant B115200 %d \"NIL\")\n", B115200);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B115200 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B115200)\n");
#ifdef B230400
    fprintf (out, "(cl:defconstant B230400 %d \"NIL\")\n", B230400);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for B230400 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'B230400)\n");
#ifdef CSIZE
    fprintf (out, "(cl:defconstant CSIZE %d \"NIL\")\n", CSIZE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CSIZE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CSIZE)\n");
#ifdef CS5
    fprintf (out, "(cl:defconstant CS5 %d \"NIL\")\n", CS5);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CS5 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CS5)\n");
#ifdef CS6
    fprintf (out, "(cl:defconstant CS6 %d \"NIL\")\n", CS6);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CS6 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CS6)\n");
#ifdef CS7
    fprintf (out, "(cl:defconstant CS7 %d \"NIL\")\n", CS7);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CS7 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CS7)\n");
#ifdef CS8
    fprintf (out, "(cl:defconstant CS8 %d \"NIL\")\n", CS8);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CS8 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CS8)\n");
#ifdef CSTOPB
    fprintf (out, "(cl:defconstant CSTOPB %d \"NIL\")\n", CSTOPB);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CSTOPB (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CSTOPB)\n");
#ifdef CREAD
    fprintf (out, "(cl:defconstant CREAD %d \"NIL\")\n", CREAD);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CREAD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CREAD)\n");
#ifdef PARENB
    fprintf (out, "(cl:defconstant PARENB %d \"NIL\")\n", PARENB);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for PARENB (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'PARENB)\n");
#ifdef PARODD
    fprintf (out, "(cl:defconstant PARODD %d \"NIL\")\n", PARODD);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for PARODD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'PARODD)\n");
#ifdef HUPCL
    fprintf (out, "(cl:defconstant HUPCL %d \"NIL\")\n", HUPCL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for HUPCL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'HUPCL)\n");
#ifdef CLOCAL
    fprintf (out, "(cl:defconstant CLOCAL %d \"NIL\")\n", CLOCAL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for CLOCAL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'CLOCAL)\n");
#ifdef ECHO
    fprintf (out, "(cl:defconstant ECHO %d \"NIL\")\n", ECHO);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECHO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECHO)\n");
#ifdef ECHOE
    fprintf (out, "(cl:defconstant ECHOE %d \"NIL\")\n", ECHOE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECHOE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECHOE)\n");
#ifdef ECHOK
    fprintf (out, "(cl:defconstant ECHOK %d \"NIL\")\n", ECHOK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECHOK (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECHOK)\n");
#ifdef ECHONL
    fprintf (out, "(cl:defconstant ECHONL %d \"NIL\")\n", ECHONL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECHONL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ECHONL)\n");
#ifdef ICANON
    fprintf (out, "(cl:defconstant ICANON %d \"NIL\")\n", ICANON);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ICANON (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ICANON)\n");
#ifdef IEXTEN
    fprintf (out, "(cl:defconstant IEXTEN %d \"NIL\")\n", IEXTEN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for IEXTEN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'IEXTEN)\n");
#ifdef ISIG
    fprintf (out, "(cl:defconstant ISIG %d \"NIL\")\n", ISIG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ISIG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'ISIG)\n");
#ifdef NOFLSH
    fprintf (out, "(cl:defconstant NOFLSH %d \"NIL\")\n", NOFLSH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NOFLSH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'NOFLSH)\n");
#ifdef TOSTOP
    fprintf (out, "(cl:defconstant TOSTOP %d \"NIL\")\n", TOSTOP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TOSTOP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TOSTOP)\n");
#ifdef TCSANOW
    fprintf (out, "(cl:defconstant TCSANOW %d \"NIL\")\n", TCSANOW);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCSANOW (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCSANOW)\n");
#ifdef TCSADRAIN
    fprintf (out, "(cl:defconstant TCSADRAIN %d \"NIL\")\n", TCSADRAIN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCSADRAIN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCSADRAIN)\n");
#ifdef TCSAFLUSH
    fprintf (out, "(cl:defconstant TCSAFLUSH %d \"NIL\")\n", TCSAFLUSH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCSAFLUSH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCSAFLUSH)\n");
#ifdef TCIFLUSH
    fprintf (out, "(cl:defconstant TCIFLUSH %d \"NIL\")\n", TCIFLUSH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCIFLUSH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCIFLUSH)\n");
#ifdef TCIOFLUSH
    fprintf (out, "(cl:defconstant TCIOFLUSH %d \"NIL\")\n", TCIOFLUSH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCIOFLUSH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCIOFLUSH)\n");
#ifdef TCOFLUSH
    fprintf (out, "(cl:defconstant TCOFLUSH %d \"NIL\")\n", TCOFLUSH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCOFLUSH (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCOFLUSH)\n");
#ifdef TCIOFF
    fprintf (out, "(cl:defconstant TCIOFF %d \"NIL\")\n", TCIOFF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCIOFF (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCIOFF)\n");
#ifdef TCION
    fprintf (out, "(cl:defconstant TCION %d \"NIL\")\n", TCION);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCION (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCION)\n");
#ifdef TCOOFF
    fprintf (out, "(cl:defconstant TCOOFF %d \"NIL\")\n", TCOOFF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCOOFF (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCOOFF)\n");
#ifdef TCOON
    fprintf (out, "(cl:defconstant TCOON %d \"NIL\")\n", TCOON);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCOON (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'TCOON)\n");
#ifdef LOG_USER
    fprintf (out, "(cl:defconstant LOG-USER %d \"Default openlog() faclity.\")\n", LOG_USER);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_USER (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-USER)\n");
#ifdef LOG_LOCAL0
    fprintf (out, "(cl:defconstant LOG-LOCAL0 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL0);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL0 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL0)\n");
#ifdef LOG_LOCAL1
    fprintf (out, "(cl:defconstant LOG-LOCAL1 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL1);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL1 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL1)\n");
#ifdef LOG_LOCAL2
    fprintf (out, "(cl:defconstant LOG-LOCAL2 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL2);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL2 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL2)\n");
#ifdef LOG_LOCAL3
    fprintf (out, "(cl:defconstant LOG-LOCAL3 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL3);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL3 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL3)\n");
#ifdef LOG_LOCAL4
    fprintf (out, "(cl:defconstant LOG-LOCAL4 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL4);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL4 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL4)\n");
#ifdef LOG_LOCAL5
    fprintf (out, "(cl:defconstant LOG-LOCAL5 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL5);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL5 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL5)\n");
#ifdef LOG_LOCAL6
    fprintf (out, "(cl:defconstant LOG-LOCAL6 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL6);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL6 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL6)\n");
#ifdef LOG_LOCAL7
    fprintf (out, "(cl:defconstant LOG-LOCAL7 %d \"Locally-defined openlog() facility\")\n", LOG_LOCAL7);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LOCAL7 (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LOCAL7)\n");
#ifdef LOG_AUTHPRIV
    fprintf (out, "(cl:defconstant LOG-AUTHPRIV %d \"openlog() facility for authorization messages\")\n", LOG_AUTHPRIV);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_AUTHPRIV (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-AUTHPRIV)\n");
#ifdef LOG_CRON
    fprintf (out, "(cl:defconstant LOG-CRON %d \"openlog() facility for cron and at daemons\")\n", LOG_CRON);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_CRON (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-CRON)\n");
#ifdef LOG_DAEMON
    fprintf (out, "(cl:defconstant LOG-DAEMON %d \"openlog() facility for arbitrary daemons\")\n", LOG_DAEMON);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_DAEMON (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-DAEMON)\n");
#ifdef LOG_FTP
    fprintf (out, "(cl:defconstant LOG-FTP %d \"openlog() facility for FTP daemons\")\n", LOG_FTP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_FTP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-FTP)\n");
#ifdef LOG_KERN
    fprintf (out, "(cl:defconstant LOG-KERN %d \"openlog() facility for kernel messages\")\n", LOG_KERN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_KERN (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-KERN)\n");
#ifdef LOG_LPR
    fprintf (out, "(cl:defconstant LOG-LPR %d \"openlog() facility for the printer subsystem\")\n", LOG_LPR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_LPR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-LPR)\n");
#ifdef LOG_MAIL
    fprintf (out, "(cl:defconstant LOG-MAIL %d \"openlog() facility for the mail subsystem\")\n", LOG_MAIL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_MAIL (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-MAIL)\n");
#ifdef LOG_NEWS
    fprintf (out, "(cl:defconstant LOG-NEWS %d \"openlog() facility for the usenet subsystem\")\n", LOG_NEWS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_NEWS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-NEWS)\n");
#ifdef LOG_SYSLOG
    fprintf (out, "(cl:defconstant LOG-SYSLOG %d \"openlog() facility for the syslog subsystem\")\n", LOG_SYSLOG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_SYSLOG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-SYSLOG)\n");
#ifdef LOG_UUCP
    fprintf (out, "(cl:defconstant LOG-UUCP %d \"openlog() facility for the UUCP subsystem\")\n", LOG_UUCP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_UUCP (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-UUCP)\n");
#ifdef LOG_PID
    fprintf (out, "(cl:defconstant LOG-PID %d \"If supplied to openlog(), log the process ID with each message\")\n", LOG_PID);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_PID (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-PID)\n");
#ifdef LOG_CONS
    fprintf (out, "(cl:defconstant LOG-CONS %d \"If supplied to openlog(), log to the system console as well as logfiles\")\n", LOG_CONS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_CONS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-CONS)\n");
#ifdef LOG_NDELAY
    fprintf (out, "(cl:defconstant LOG-NDELAY %d \"If supplied to openlog(), immediately open the syslog connection.\")\n", LOG_NDELAY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_NDELAY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-NDELAY)\n");
#ifdef LOG_ODELAY
    fprintf (out, "(cl:defconstant LOG-ODELAY %d \"If supplied to openlog(), delay opening the syslog connection to the first syslog() call.\")\n", LOG_ODELAY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_ODELAY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-ODELAY)\n");
#ifdef LOG_NOWAIT
    fprintf (out, "(cl:defconstant LOG-NOWAIT %d \"If supplied to openlog(), do not wait for child processes created by calls to syslog().\")\n", LOG_NOWAIT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_NOWAIT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-NOWAIT)\n");
#ifdef LOG_PERROR
    fprintf (out, "(cl:defconstant LOG-PERROR %d \"If supplied to openlog(), write log messages to the process's standard error descriptor in addition to the logging facility.\")\n", LOG_PERROR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_PERROR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-PERROR)\n");
#ifdef LOG_EMERG
    fprintf (out, "(cl:defconstant LOG-EMERG %d \"Log severity level denoting a panic.\")\n", LOG_EMERG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_EMERG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-EMERG)\n");
#ifdef LOG_ALERT
    fprintf (out, "(cl:defconstant LOG-ALERT %d \"Log severity level denoting a condition that should be corrected immediately.\")\n", LOG_ALERT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_ALERT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-ALERT)\n");
#ifdef LOG_CRIT
    fprintf (out, "(cl:defconstant LOG-CRIT %d \"Log severity level denoting critical conditions.\")\n", LOG_CRIT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_CRIT (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-CRIT)\n");
#ifdef LOG_ERR
    fprintf (out, "(cl:defconstant LOG-ERR %d \"Log severity level denoting an error.\")\n", LOG_ERR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_ERR (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-ERR)\n");
#ifdef LOG_WARNING
    fprintf (out, "(cl:defconstant LOG-WARNING %d \"Log severity level denoting a warning.\")\n", LOG_WARNING);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_WARNING (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-WARNING)\n");
#ifdef LOG_NOTICE
    fprintf (out, "(cl:defconstant LOG-NOTICE %d \"Log severity level denoting non-errors that may require special handling.\")\n", LOG_NOTICE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_NOTICE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-NOTICE)\n");
#ifdef LOG_INFO
    fprintf (out, "(cl:defconstant LOG-INFO %d \"Log severity level denoting informational messages.\")\n", LOG_INFO);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_INFO (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-INFO)\n");
#ifdef LOG_DEBUG
    fprintf (out, "(cl:defconstant LOG-DEBUG %d \"Log severity level denoting debugging information .\")\n", LOG_DEBUG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for LOG_DEBUG (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:export 'LOG-DEBUG)\n");
return 0;
}
