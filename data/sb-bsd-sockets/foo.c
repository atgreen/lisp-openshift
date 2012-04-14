#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <netdb.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <fcntl.h>
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
    fprintf (out, "(cl:in-package #:SOCKINT)\n");
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
#ifdef AF_UNSPEC
    fprintf (out, "(cl:defconstant AF-UNSPEC %d \"Unspecified\")\n", AF_UNSPEC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for AF_UNSPEC (unknown to the C compiler).\")\n");
#endif
#ifdef AF_LOCAL
    fprintf (out, "(cl:defconstant AF-LOCAL %d \"Local to host (pipes and file-domain).\")\n", AF_LOCAL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for AF_LOCAL (unknown to the C compiler).\")\n");
#endif
#ifdef AF_INET6
    fprintf (out, "(cl:defconstant AF-INET6 %d \"IP version 6\")\n", AF_INET6);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for AF_INET6 (unknown to the C compiler).\")\n");
#endif
#ifdef AF_NETLINK
    fprintf (out, "(cl:defconstant AF-ROUTE %d \"Alias to emulate 4.4BSD \")\n", AF_NETLINK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for AF_NETLINK (unknown to the C compiler).\")\n");
#endif
#ifdef SOCK_STREAM
    fprintf (out, "(cl:defconstant SOCK-STREAM %d \"Sequenced, reliable, connection-based byte streams.\")\n", SOCK_STREAM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SOCK_STREAM (unknown to the C compiler).\")\n");
#endif
#ifdef SOCK_DGRAM
    fprintf (out, "(cl:defconstant SOCK-DGRAM %d \"Connectionless, unreliable datagrams of fixed maximum length.\")\n", SOCK_DGRAM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SOCK_DGRAM (unknown to the C compiler).\")\n");
#endif
#ifdef SOCK_RAW
    fprintf (out, "(cl:defconstant SOCK-RAW %d \"Raw protocol interface.\")\n", SOCK_RAW);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SOCK_RAW (unknown to the C compiler).\")\n");
#endif
#ifdef SOCK_RDM
    fprintf (out, "(cl:defconstant SOCK-RDM %d \"Reliably-delivered messages.\")\n", SOCK_RDM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SOCK_RDM (unknown to the C compiler).\")\n");
#endif
#ifdef SOCK_SEQPACKET
    fprintf (out, "(cl:defconstant SOCK-SEQPACKET %d \"Sequenced, reliable, connection-based, datagrams of fixed maximum length.\")\n", SOCK_SEQPACKET);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SOCK_SEQPACKET (unknown to the C compiler).\")\n");
#endif
#ifdef SOL_SOCKET
    fprintf (out, "(cl:defconstant SOL-SOCKET %d \"NIL\")\n", SOL_SOCKET);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SOL_SOCKET (unknown to the C compiler).\")\n");
#endif
#ifdef SO_DEBUG
    fprintf (out, "(cl:defconstant SO-DEBUG %d \"Enable debugging in underlying protocol modules\")\n", SO_DEBUG);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_DEBUG (unknown to the C compiler).\")\n");
#endif
#ifdef SO_REUSEADDR
    fprintf (out, "(cl:defconstant SO-REUSEADDR %d \"Enable local address reuse\")\n", SO_REUSEADDR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_REUSEADDR (unknown to the C compiler).\")\n");
#endif
#ifdef SO_TYPE
    fprintf (out, "(cl:defconstant SO-TYPE %d \"NIL\")\n", SO_TYPE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_TYPE (unknown to the C compiler).\")\n");
#endif
#ifdef SO_ERROR
    fprintf (out, "(cl:defconstant SO-ERROR %d \"NIL\")\n", SO_ERROR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_ERROR (unknown to the C compiler).\")\n");
#endif
#ifdef SO_DONTROUTE
    fprintf (out, "(cl:defconstant SO-DONTROUTE %d \"Bypass routing facilities: instead send direct to appropriate network interface for the network portion of the destination address\")\n", SO_DONTROUTE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_DONTROUTE (unknown to the C compiler).\")\n");
#endif
#ifdef SO_BROADCAST
    fprintf (out, "(cl:defconstant SO-BROADCAST %d \"Request permission to send broadcast datagrams\")\n", SO_BROADCAST);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_BROADCAST (unknown to the C compiler).\")\n");
#endif
#ifdef SO_SNDBUF
    fprintf (out, "(cl:defconstant SO-SNDBUF %d \"NIL\")\n", SO_SNDBUF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_SNDBUF (unknown to the C compiler).\")\n");
#endif
#ifdef SO_PASSCRED
    fprintf (out, "(cl:defconstant SO-PASSCRED %d \"NIL\")\n", SO_PASSCRED);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_PASSCRED (unknown to the C compiler).\")\n");
#endif
#ifdef SO_RCVBUF
    fprintf (out, "(cl:defconstant SO-RCVBUF %d \"NIL\")\n", SO_RCVBUF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_RCVBUF (unknown to the C compiler).\")\n");
#endif
#ifdef SO_KEEPALIVE
    fprintf (out, "(cl:defconstant SO-KEEPALIVE %d \"Send periodic keepalives: if peer does not respond, we get SIGPIPE\")\n", SO_KEEPALIVE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_KEEPALIVE (unknown to the C compiler).\")\n");
#endif
#ifdef SO_OOBINLINE
    fprintf (out, "(cl:defconstant SO-OOBINLINE %d \"Put out-of-band data into the normal input queue when received\")\n", SO_OOBINLINE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_OOBINLINE (unknown to the C compiler).\")\n");
#endif
#ifdef SO_NO_CHECK
    fprintf (out, "(cl:defconstant SO-NO-CHECK %d \"NIL\")\n", SO_NO_CHECK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_NO_CHECK (unknown to the C compiler).\")\n");
#endif
#ifdef SO_PRIORITY
    fprintf (out, "(cl:defconstant SO-PRIORITY %d \"NIL\")\n", SO_PRIORITY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_PRIORITY (unknown to the C compiler).\")\n");
#endif
#ifdef SO_LINGER
    fprintf (out, "(cl:defconstant SO-LINGER %d \"For reliable streams, pause a while on closing when unsent messages are queued\")\n", SO_LINGER);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_LINGER (unknown to the C compiler).\")\n");
#endif
#ifdef SO_BSDCOMPAT
    fprintf (out, "(cl:defconstant SO-BSDCOMPAT %d \"NIL\")\n", SO_BSDCOMPAT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_BSDCOMPAT (unknown to the C compiler).\")\n");
#endif
#ifdef SO_SNDLOWAT
    fprintf (out, "(cl:defconstant SO-SNDLOWAT %d \"NIL\")\n", SO_SNDLOWAT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_SNDLOWAT (unknown to the C compiler).\")\n");
#endif
#ifdef SO_RCVLOWAT
    fprintf (out, "(cl:defconstant SO-RCVLOWAT %d \"NIL\")\n", SO_RCVLOWAT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_RCVLOWAT (unknown to the C compiler).\")\n");
#endif
#ifdef SO_SNDTIMEO
    fprintf (out, "(cl:defconstant SO-SNDTIMEO %d \"NIL\")\n", SO_SNDTIMEO);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_SNDTIMEO (unknown to the C compiler).\")\n");
#endif
#ifdef SO_RCVTIMEO
    fprintf (out, "(cl:defconstant SO-RCVTIMEO %d \"NIL\")\n", SO_RCVTIMEO);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_RCVTIMEO (unknown to the C compiler).\")\n");
#endif
#ifdef TCP_NODELAY
    fprintf (out, "(cl:defconstant TCP-NODELAY %d \"NIL\")\n", TCP_NODELAY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TCP_NODELAY (unknown to the C compiler).\")\n");
#endif
#ifdef SO_BINDTODEVICE
    fprintf (out, "(cl:defconstant SO-BINDTODEVICE %d \"NIL\")\n", SO_BINDTODEVICE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for SO_BINDTODEVICE (unknown to the C compiler).\")\n");
#endif
#ifdef IFNAMSIZ
    fprintf (out, "(cl:defconstant IFNAMSIZ %d \"NIL\")\n", IFNAMSIZ);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for IFNAMSIZ (unknown to the C compiler).\")\n");
#endif
#ifdef EADDRINUSE
    fprintf (out, "(cl:defconstant EADDRINUSE %d \"NIL\")\n", EADDRINUSE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EADDRINUSE (unknown to the C compiler).\")\n");
#endif
#ifdef EAGAIN
    fprintf (out, "(cl:defconstant EAGAIN %d \"NIL\")\n", EAGAIN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAGAIN (unknown to the C compiler).\")\n");
#endif
#ifdef EBADF
    fprintf (out, "(cl:defconstant EBADF %d \"NIL\")\n", EBADF);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EBADF (unknown to the C compiler).\")\n");
#endif
#ifdef ECONNREFUSED
    fprintf (out, "(cl:defconstant ECONNREFUSED %d \"NIL\")\n", ECONNREFUSED);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ECONNREFUSED (unknown to the C compiler).\")\n");
#endif
#ifdef ETIMEDOUT
    fprintf (out, "(cl:defconstant ETIMEDOUT %d \"NIL\")\n", ETIMEDOUT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ETIMEDOUT (unknown to the C compiler).\")\n");
#endif
#ifdef EINTR
    fprintf (out, "(cl:defconstant EINTR %d \"NIL\")\n", EINTR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EINTR (unknown to the C compiler).\")\n");
#endif
#ifdef EINVAL
    fprintf (out, "(cl:defconstant EINVAL %d \"NIL\")\n", EINVAL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EINVAL (unknown to the C compiler).\")\n");
#endif
#ifdef ENOBUFS
    fprintf (out, "(cl:defconstant ENOBUFS %d \"NIL\")\n", ENOBUFS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOBUFS (unknown to the C compiler).\")\n");
#endif
#ifdef ENOMEM
    fprintf (out, "(cl:defconstant ENOMEM %d \"NIL\")\n", ENOMEM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOMEM (unknown to the C compiler).\")\n");
#endif
#ifdef EOPNOTSUPP
    fprintf (out, "(cl:defconstant EOPNOTSUPP %d \"NIL\")\n", EOPNOTSUPP);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EOPNOTSUPP (unknown to the C compiler).\")\n");
#endif
#ifdef EPERM
    fprintf (out, "(cl:defconstant EPERM %d \"NIL\")\n", EPERM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPERM (unknown to the C compiler).\")\n");
#endif
#ifdef EPROTONOSUPPORT
    fprintf (out, "(cl:defconstant EPROTONOSUPPORT %d \"NIL\")\n", EPROTONOSUPPORT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EPROTONOSUPPORT (unknown to the C compiler).\")\n");
#endif
#ifdef ESOCKTNOSUPPORT
    fprintf (out, "(cl:defconstant ESOCKTNOSUPPORT %d \"NIL\")\n", ESOCKTNOSUPPORT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ESOCKTNOSUPPORT (unknown to the C compiler).\")\n");
#endif
#ifdef ENETUNREACH
    fprintf (out, "(cl:defconstant ENETUNREACH %d \"NIL\")\n", ENETUNREACH);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENETUNREACH (unknown to the C compiler).\")\n");
#endif
#ifdef ENOTCONN
    fprintf (out, "(cl:defconstant ENOTCONN %d \"NIL\")\n", ENOTCONN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for ENOTCONN (unknown to the C compiler).\")\n");
#endif
#ifdef NETDB_INTERNAL
    fprintf (out, "(cl:defconstant NETDB-INTERNAL %d \"See errno.\")\n", NETDB_INTERNAL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NETDB_INTERNAL (unknown to the C compiler).\")\n");
#endif
#ifdef NETDB_SUCCESS
    fprintf (out, "(cl:defconstant NETDB-SUCCESS %d \"No problem.\")\n", NETDB_SUCCESS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NETDB_SUCCESS (unknown to the C compiler).\")\n");
#endif
#ifdef HOST_NOT_FOUND
    fprintf (out, "(cl:defconstant HOST-NOT-FOUND %d \"Authoritative Answer Host not found.\")\n", HOST_NOT_FOUND);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for HOST_NOT_FOUND (unknown to the C compiler).\")\n");
#endif
#ifdef TRY_AGAIN
    fprintf (out, "(cl:defconstant TRY-AGAIN %d \"Non-Authoritative Host not found, or SERVERFAIL.\")\n", TRY_AGAIN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for TRY_AGAIN (unknown to the C compiler).\")\n");
#endif
#ifdef NO_RECOVERY
    fprintf (out, "(cl:defconstant NO-RECOVERY %d \"Non recoverable errors, FORMERR, REFUSED, NOTIMP.\")\n", NO_RECOVERY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NO_RECOVERY (unknown to the C compiler).\")\n");
#endif
#ifdef NO_DATA
    fprintf (out, "(cl:defconstant NO-DATA %d \"Valid name, no data record of requested type.\")\n", NO_DATA);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NO_DATA (unknown to the C compiler).\")\n");
#endif
#ifdef NO_ADDRESS
    fprintf (out, "(cl:defconstant NO-ADDRESS %d \"No address, look for MX record.\")\n", NO_ADDRESS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NO_ADDRESS (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:declaim (cl:inline H-STRERROR))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"hstrerror\" H-STRERROR)\n");
    fprintf (out, "  C-STRING\n  (ERRNO INT))\n");
#ifdef O_NONBLOCK
    fprintf (out, "(cl:defconstant O-NONBLOCK %d \"NIL\")\n", O_NONBLOCK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for O_NONBLOCK (unknown to the C compiler).\")\n");
#endif
#ifdef F_GETFL
    fprintf (out, "(cl:defconstant F-GETFL %d \"NIL\")\n", F_GETFL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_GETFL (unknown to the C compiler).\")\n");
#endif
#ifdef F_SETFL
    fprintf (out, "(cl:defconstant F-SETFL %d \"NIL\")\n", F_SETFL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for F_SETFL (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_OOB
    fprintf (out, "(cl:defconstant MSG-OOB %d \"NIL\")\n", MSG_OOB);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_OOB (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_PEEK
    fprintf (out, "(cl:defconstant MSG-PEEK %d \"NIL\")\n", MSG_PEEK);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_PEEK (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_TRUNC
    fprintf (out, "(cl:defconstant MSG-TRUNC %d \"NIL\")\n", MSG_TRUNC);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_TRUNC (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_WAITALL
    fprintf (out, "(cl:defconstant MSG-WAITALL %d \"NIL\")\n", MSG_WAITALL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_WAITALL (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_EOR
    fprintf (out, "(cl:defconstant MSG-EOR %d \"NIL\")\n", MSG_EOR);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_EOR (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_DONTROUTE
    fprintf (out, "(cl:defconstant MSG-DONTROUTE %d \"NIL\")\n", MSG_DONTROUTE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_DONTROUTE (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_DONTWAIT
    fprintf (out, "(cl:defconstant MSG-DONTWAIT %d \"NIL\")\n", MSG_DONTWAIT);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_DONTWAIT (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_NOSIGNAL
    fprintf (out, "(cl:defconstant MSG-NOSIGNAL %d \"NIL\")\n", MSG_NOSIGNAL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_NOSIGNAL (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_CONFIRM
    fprintf (out, "(cl:defconstant MSG-CONFIRM %d \"NIL\")\n", MSG_CONFIRM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_CONFIRM (unknown to the C compiler).\")\n");
#endif
#ifdef MSG_MORE
    fprintf (out, "(cl:defconstant MSG-MORE %d \"NIL\")\n", MSG_MORE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for MSG_MORE (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type SOCKLEN-T (sb-alien:%ssigned %d)))\n", SIGNED_(socklen_t), (8*sizeof(socklen_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type SIZE-T (sb-alien:%ssigned %d)))\n", SIGNED_(size_t), (8*sizeof(size_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-alien:define-alien-type SSIZE-T (sb-alien:%ssigned %d)))\n", SIGNED_(ssize_t), (8*sizeof(ssize_t)));
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct PROTOENT %d\n", sizeof(struct protoent));
    fprintf (out, " (NAME C-STRING-POINTER \"char *\"\n");
{ struct protoent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.p_name)) - ((unsigned long)&(t)));
}
{ struct protoent t;
    fprintf (out, "  %d)\n", sizeof(t.p_name));
}
    fprintf (out, " (ALIASES (* (* T)) \"char **\"\n");
{ struct protoent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.p_aliases)) - ((unsigned long)&(t)));
}
{ struct protoent t;
    fprintf (out, "  %d)\n", sizeof(t.p_aliases));
}
    fprintf (out, " (PROTO INTEGER \"int\"\n");
{ struct protoent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.p_proto)) - ((unsigned long)&(t)));
}
{ struct protoent t;
    fprintf (out, "  %d)\n", sizeof(t.p_proto));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:declaim (cl:inline GETPROTOBYNAME))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"getprotobyname\" GETPROTOBYNAME)\n");
    fprintf (out, "  (* PROTOENT)\n  (NAME C-STRING))\n");
    fprintf (out, "(cl:declaim (cl:inline GETPROTOBYNUMBER))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"getprotobynumber\" GETPROTOBYNUMBER)\n");
    fprintf (out, "  (* PROTOENT)\n  (PROTO INT))\n");
#ifdef INADDR_ANY
    fprintf (out, "(cl:defconstant INADDR-ANY %d \"NIL\")\n", INADDR_ANY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for INADDR_ANY (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct IN-ADDR %d\n", sizeof(struct in_addr));
    fprintf (out, " (ADDR (ARRAY (UNSIGNED 8)) \"u_int32_t\"\n");
{ struct in_addr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.s_addr)) - ((unsigned long)&(t)));
}
{ struct in_addr t;
    fprintf (out, "  %d)\n", sizeof(t.s_addr));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct SOCKADDR-IN %d\n", sizeof(struct sockaddr_in));
    fprintf (out, " (FAMILY INTEGER \"sa_family_t\"\n");
{ struct sockaddr_in t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.sin_family)) - ((unsigned long)&(t)));
}
{ struct sockaddr_in t;
    fprintf (out, "  %d)\n", sizeof(t.sin_family));
}
    fprintf (out, " (PORT (ARRAY (UNSIGNED 8)) \"u_int16_t\"\n");
{ struct sockaddr_in t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.sin_port)) - ((unsigned long)&(t)));
}
{ struct sockaddr_in t;
    fprintf (out, "  %d)\n", sizeof(t.sin_port));
}
    fprintf (out, " (ADDR (ARRAY (UNSIGNED 8)) \"struct in_addr\"\n");
{ struct sockaddr_in t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.sin_addr)) - ((unsigned long)&(t)));
}
{ struct sockaddr_in t;
    fprintf (out, "  %d)\n", sizeof(t.sin_addr));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct SOCKADDR-UN %d\n", sizeof(struct sockaddr_un));
    fprintf (out, " (FAMILY INTEGER \"sa_family_t\"\n");
{ struct sockaddr_un t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.sun_family)) - ((unsigned long)&(t)));
}
{ struct sockaddr_un t;
    fprintf (out, "  %d)\n", sizeof(t.sun_family));
}
    fprintf (out, " (PATH C-STRING \"char\"\n");
{ struct sockaddr_un t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.sun_path)) - ((unsigned long)&(t)));
}
{ struct sockaddr_un t;
    fprintf (out, "  %d)\n", sizeof(t.sun_path));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct SOCKADDR-UN-ABSTRACT %d\n", sizeof(struct sockaddr_un));
    fprintf (out, " (FAMILY INTEGER \"sa_family_t\"\n");
{ struct sockaddr_un t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.sun_family)) - ((unsigned long)&(t)));
}
{ struct sockaddr_un t;
    fprintf (out, "  %d)\n", sizeof(t.sun_family));
}
    fprintf (out, " (PATH (ARRAY (UNSIGNED 8)) \"char\"\n");
{ struct sockaddr_un t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.sun_path)) - ((unsigned long)&(t)));
}
{ struct sockaddr_un t;
    fprintf (out, "  %d)\n", sizeof(t.sun_path));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct HOSTENT %d\n", sizeof(struct hostent));
    fprintf (out, " (NAME C-STRING-POINTER \"char *\"\n");
{ struct hostent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.h_name)) - ((unsigned long)&(t)));
}
{ struct hostent t;
    fprintf (out, "  %d)\n", sizeof(t.h_name));
}
    fprintf (out, " (ALIASES (* C-STRING) \"char **\"\n");
{ struct hostent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.h_aliases)) - ((unsigned long)&(t)));
}
{ struct hostent t;
    fprintf (out, "  %d)\n", sizeof(t.h_aliases));
}
    fprintf (out, " (TYPE INTEGER \"int\"\n");
{ struct hostent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.h_addrtype)) - ((unsigned long)&(t)));
}
{ struct hostent t;
    fprintf (out, "  %d)\n", sizeof(t.h_addrtype));
}
    fprintf (out, " (LENGTH INTEGER \"int\"\n");
{ struct hostent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.h_length)) - ((unsigned long)&(t)));
}
{ struct hostent t;
    fprintf (out, "  %d)\n", sizeof(t.h_length));
}
    fprintf (out, " (ADDRESSES (* (* (UNSIGNED 8))) \"char **\"\n");
{ struct hostent t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.h_addr_list)) - ((unsigned long)&(t)));
}
{ struct hostent t;
    fprintf (out, "  %d)\n", sizeof(t.h_addr_list));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct MSGHDR %d\n", sizeof(struct msghdr));
    fprintf (out, " (NAME C-STRING-POINTER \"void *\"\n");
{ struct msghdr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.msg_name)) - ((unsigned long)&(t)));
}
{ struct msghdr t;
    fprintf (out, "  %d)\n", sizeof(t.msg_name));
}
    fprintf (out, " (NAMELEN INTEGER \"socklen_t\"\n");
{ struct msghdr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.msg_namelen)) - ((unsigned long)&(t)));
}
{ struct msghdr t;
    fprintf (out, "  %d)\n", sizeof(t.msg_namelen));
}
    fprintf (out, " (IOV (* T) \"struct iovec\"\n");
{ struct msghdr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.msg_iov)) - ((unsigned long)&(t)));
}
{ struct msghdr t;
    fprintf (out, "  %d)\n", sizeof(t.msg_iov));
}
    fprintf (out, " (IOVLEN INTEGER \"size_t\"\n");
{ struct msghdr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.msg_iovlen)) - ((unsigned long)&(t)));
}
{ struct msghdr t;
    fprintf (out, "  %d)\n", sizeof(t.msg_iovlen));
}
    fprintf (out, " (CONTROL (* T) \"void *\"\n");
{ struct msghdr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.msg_control)) - ((unsigned long)&(t)));
}
{ struct msghdr t;
    fprintf (out, "  %d)\n", sizeof(t.msg_control));
}
    fprintf (out, " (CONTROLLEN INTEGER \"socklen_t\"\n");
{ struct msghdr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.msg_controllen)) - ((unsigned long)&(t)));
}
{ struct msghdr t;
    fprintf (out, "  %d)\n", sizeof(t.msg_controllen));
}
    fprintf (out, " (FLAGS INTEGER \"int\"\n");
{ struct msghdr t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.msg_flags)) - ((unsigned long)&(t)));
}
{ struct msghdr t;
    fprintf (out, "  %d)\n", sizeof(t.msg_flags));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:declaim (cl:inline SOCKET))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"socket\" SOCKET)\n");
    fprintf (out, "  INT\n  (DOMAIN INT)\n  (TYPE INT)\n  (PROTOCOL INT))\n");
    fprintf (out, "(cl:declaim (cl:inline BIND))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"bind\" BIND)\n");
    fprintf (out, "  INT\n  (SOCKFD INT)\n  (MY-ADDR (* T))\n  (ADDRLEN SOCKLEN-T))\n");
    fprintf (out, "(cl:declaim (cl:inline LISTEN))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"listen\" LISTEN)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (BACKLOG INT))\n");
    fprintf (out, "(cl:declaim (cl:inline ACCEPT))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"accept\" ACCEPT)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (MY-ADDR (* T))\n  (ADDRLEN SOCKLEN-T :IN-OUT))\n");
    fprintf (out, "(cl:declaim (cl:inline GETPEERNAME))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"getpeername\" GETPEERNAME)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (HER-ADDR (* T))\n  (ADDRLEN SOCKLEN-T :IN-OUT))\n");
    fprintf (out, "(cl:declaim (cl:inline GETSOCKNAME))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"getsockname\" GETSOCKNAME)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (MY-ADDR (* T))\n  (ADDRLEN SOCKLEN-T :IN-OUT))\n");
    fprintf (out, "(cl:declaim (cl:inline CONNECT))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"connect\" CONNECT)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (HIS-ADDR (* T))\n  (ADDRLEN SOCKLEN-T))\n");
    fprintf (out, "(cl:declaim (cl:inline CLOSE))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"close\" CLOSE)\n");
    fprintf (out, "  INT\n  (FD INT))\n");
    fprintf (out, "(cl:declaim (cl:inline RECVFROM))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"recvfrom\" RECVFROM)\n");
    fprintf (out, "  SSIZE-T\n  (SOCKET INT)\n  (BUF (* T))\n  (LEN INTEGER)\n  (FLAGS INT)\n  (SOCKADDR (* T))\n  (SOCKLEN (* SOCKLEN-T)))\n");
    fprintf (out, "(cl:declaim (cl:inline RECVMSG))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"recvmsg\" RECVMSG)\n");
    fprintf (out, "  SSIZE-T\n  (SOCKET INT)\n  (MSG (* MSGHDR))\n  (FLAGS INT))\n");
    fprintf (out, "(cl:declaim (cl:inline SEND))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"send\" SEND)\n");
    fprintf (out, "  SSIZE-T\n  (SOCKET INT)\n  (BUF (* T))\n  (LEN SIZE-T)\n  (FLAGS INT))\n");
    fprintf (out, "(cl:declaim (cl:inline SENDTO))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"sendto\" SENDTO)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (BUF (* T))\n  (LEN SIZE-T)\n  (FLAGS INT)\n  (SOCKADDR (* T))\n  (SOCKLEN SOCKLEN-T))\n");
    fprintf (out, "(cl:declaim (cl:inline SENDMSG))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"sendmsg\" SENDMSG)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (MSG (* MSGHDR))\n  (FLAGS INT))\n");
    fprintf (out, "(cl:declaim (cl:inline GETHOSTBYNAME))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"gethostbyname\" GETHOSTBYNAME)\n");
    fprintf (out, "  (* HOSTENT)\n  (NAME C-STRING))\n");
    fprintf (out, "(cl:declaim (cl:inline GETHOSTBYADDR))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"gethostbyaddr\" GETHOSTBYADDR)\n");
    fprintf (out, "  (* HOSTENT)\n  (ADDR (* T))\n  (LEN INT)\n  (AF INT))\n");
    fprintf (out, "(cl:declaim (cl:inline GETHOSTBYNAME-R))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"gethostbyname_r\" GETHOSTBYNAME-R)\n");
    fprintf (out, "  INT\n  (NAME C-STRING)\n  (RET (* HOSTENT))\n  (BUF (* CHAR))\n  (BUFLEN LONG)\n  (RESULT (* (* HOSTENT)))\n  (H-ERRNOP (* INT)))\n");
    fprintf (out, "(cl:eval-when (:compile-toplevel :load-toplevel :execute) (sb-grovel::define-c-struct ADDRINFO %d\n", sizeof(struct addrinfo));
    fprintf (out, " (FLAGS INTEGER \"int\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_flags)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_flags));
}
    fprintf (out, " (FAMILY INTEGER \"int\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_family)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_family));
}
    fprintf (out, " (SOCKTYPE INTEGER \"int\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_socktype)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_socktype));
}
    fprintf (out, " (PROTOCOL INTEGER \"int\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_protocol)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_protocol));
}
    fprintf (out, " (ADDRLEN INTEGER \"size_t\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_addrlen)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_addrlen));
}
    fprintf (out, " (ADDR (* SOCKADDR-IN) \"struct sockaddr*\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_addr)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_addr));
}
    fprintf (out, " (CANONNAME C-STRING \"char *\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_canonname)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_canonname));
}
    fprintf (out, " (NEXT (* T) \"struct addrinfo*\"\n");
{ struct addrinfo t;
    fprintf (out, "  %d\n", ((unsigned long)&(t.ai_next)) - ((unsigned long)&(t)));
}
{ struct addrinfo t;
    fprintf (out, "  %d)\n", sizeof(t.ai_next));
}
    fprintf (out, "))\n");
    fprintf (out, "(cl:declaim (cl:inline GETADDRINFO))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"getaddrinfo\" GETADDRINFO)\n");
    fprintf (out, "  INT\n  (NODE C-STRING)\n  (SERVICE C-STRING)\n  (HINTS (* ADDRINFO))\n  (RES (* (* ADDRINFO))))\n");
    fprintf (out, "(cl:declaim (cl:inline FREEADDRINFO))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"freeaddrinfo\" FREEADDRINFO)\n");
    fprintf (out, "  VOID\n  (RES (* ADDRINFO)))\n");
    fprintf (out, "(cl:declaim (cl:inline GAI-STRERROR))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"gai_strerror\" GAI-STRERROR)\n");
    fprintf (out, "  C-STRING\n  (ERROR-CODE INT))\n");
    fprintf (out, "(cl:declaim (cl:inline GETNAMEINFO))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"getnameinfo\" GETNAMEINFO)\n");
    fprintf (out, "  INT\n  (ADDRESS (* SOCKADDR-IN))\n  (ADDRESS-LENGTH SIZE-T)\n  (HOST (* CHAR))\n  (HOST-LEN SIZE-T)\n  (SERVICE (* CHAR))\n  (SERVICE-LEN SIZE-T)\n  (FLAGS INT))\n");
#ifdef EAI_FAMILY
    fprintf (out, "(cl:defconstant EAI-FAMILY %d \"NIL\")\n", EAI_FAMILY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_FAMILY (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_SOCKTYPE
    fprintf (out, "(cl:defconstant EAI-SOCKTYPE %d \"NIL\")\n", EAI_SOCKTYPE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_SOCKTYPE (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_BADFLAGS
    fprintf (out, "(cl:defconstant EAI-BADFLAGS %d \"NIL\")\n", EAI_BADFLAGS);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_BADFLAGS (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_NONAME
    fprintf (out, "(cl:defconstant EAI-NONAME %d \"NIL\")\n", EAI_NONAME);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_NONAME (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_SERVICE
    fprintf (out, "(cl:defconstant EAI-SERVICE %d \"NIL\")\n", EAI_SERVICE);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_SERVICE (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_ADDRFAMILY
    fprintf (out, "(cl:defconstant EAI-ADDRFAMILY %d \"NIL\")\n", EAI_ADDRFAMILY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_ADDRFAMILY (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_MEMORY
    fprintf (out, "(cl:defconstant EAI-MEMORY %d \"NIL\")\n", EAI_MEMORY);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_MEMORY (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_FAIL
    fprintf (out, "(cl:defconstant EAI-FAIL %d \"NIL\")\n", EAI_FAIL);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_FAIL (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_AGAIN
    fprintf (out, "(cl:defconstant EAI-AGAIN %d \"NIL\")\n", EAI_AGAIN);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_AGAIN (unknown to the C compiler).\")\n");
#endif
#ifdef EAI_SYSTEM
    fprintf (out, "(cl:defconstant EAI-SYSTEM %d \"NIL\")\n", EAI_SYSTEM);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for EAI_SYSTEM (unknown to the C compiler).\")\n");
#endif
#ifdef NI_NAMEREQD
    fprintf (out, "(cl:defconstant NI-NAMEREQD %d \"NIL\")\n", NI_NAMEREQD);
#else
    fprintf (out, "(sb-int:style-warn \"Couldn't grovel for NI_NAMEREQD (unknown to the C compiler).\")\n");
#endif
    fprintf (out, "(cl:declaim (cl:inline SETSOCKOPT))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"setsockopt\" SETSOCKOPT)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (LEVEL INT)\n  (OPTNAME INT)\n  (OPTVAL (* T))\n  (OPTLEN INT))\n");
    fprintf (out, "(cl:declaim (cl:inline FCNTL))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"fcntl\" FCNTL)\n");
    fprintf (out, "  INT\n  (FD INT)\n  (CMD INT)\n  (ARG LONG))\n");
    fprintf (out, "(cl:declaim (cl:inline GETSOCKOPT))\n");
    fprintf (out, "(sb-grovel::define-foreign-routine (\"getsockopt\" GETSOCKOPT)\n");
    fprintf (out, "  INT\n  (SOCKET INT)\n  (LEVEL INT)\n  (OPTNAME INT)\n  (OPTVAL (* T))\n  (OPTLEN (* INT)))\n");
return 0;
}
