noinst_LIBRARIES += lib/libopenflow.a

lib_libopenflow_a_SOURCES = \
	lib/backtrace.c \
	lib/backtrace.h \
	lib/command-line.c \
	lib/command-line.h \
	lib/daemon.c \
	lib/daemon.h \
	lib/dirs.c \
	lib/dirs.h \
	lib/dynamic-string.c \
	lib/dynamic-string.h \
	lib/fatal-signal.c \
	lib/fatal-signal.h \
	lib/flow.c \
	lib/flow.h \
	lib/hash.c \
	lib/hash.h \
	lib/hmap.c \
	lib/hmap.h \
	lib/ipv6_util.c \
	lib/ipv6_util.h \
	lib/leak-checker.c \
	lib/leak-checker.h \
	lib/list.c \
	lib/list.h \
	lib/ofp.c \
	lib/ofp.h \
	lib/ofpbuf.c \
	lib/ofpbuf.h \
	lib/ofp.c \
	lib/ofp.h \
    lib/ofpstat.c \
    lib/packets.h \
	lib/poll-loop.c \
	lib/poll-loop.h \
	lib/random.c \
	lib/random.h \
	lib/socket-util.c \
	lib/socket-util.h \
	lib/timeval.c \
	lib/timeval.h \
	lib/type-props.h \
	lib/util.c \
    lib/util.h \
	lib/vconn-stream.c \
	lib/vconn-stream.h \
	lib/vconn-tcp.c \
	lib/vconn-unix.c \
	lib/vconn.c \
	lib/vconn.h \
	lib/vlog-modules.def \
	lib/vlog-socket.c \
	lib/vlog-socket.h \
	lib/vlog.c \
	lib/vlog.h \
	lib/xtoxll.h

lib_libopenflow_a_LIBADD = oflib/ofl-actions.o \
                           oflib/ofl-actions-pack.o \
                           oflib/ofl-actions-print.o \
                           oflib/ofl-actions-unpack.o \
                           oflib/ofl-messages.o \
                           oflib/ofl-messages-pack.o \
                           oflib/ofl-messages-print.o \
                           oflib/ofl-messages-unpack.o \
                           oflib/ofl-structs.o \
			               oflib/ofl-structs-match.o \
                           oflib/ofl-structs-pack.o \
                           oflib/ofl-structs-print.o \
                           oflib/ofl-structs-unpack.o \
                           oflib/oxm-match.o \
                           oflib/ofl-print.o \
                           oflib-exp/ofl-exp.o \
                           oflib-exp/ofl-exp-openflow.o


if HAVE_NETLINK
lib_libopenflow_a_SOURCES += \
	lib/dpif.c \
	lib/dpif.h \
	lib/netlink-protocol.h \
	lib/netlink.c \
	lib/netlink.h \
	lib/vconn-netlink.c
endif

#CLEANFILES += lib/dirs.c
#lib/dirs.c: Makefile
#	($(ro_c) && \
#	 echo 'const char ofp_pkgdatadir[] = "$(pkgdatadir)";' && \
#	 echo 'const char ofp_rundir[] = "@RUNDIR@";' && \
#	 echo 'const char ofp_logdir[] = "@LOGDIR@";') > lib/dirs.c.tmp
#	mv lib/dirs.c.tmp lib/dirs.c

install-data-local:
	$(MKDIR_P) $(DESTDIR)$(RUNDIR)
	$(MKDIR_P) $(DESTDIR)$(PKIDIR)
	$(MKDIR_P) $(DESTDIR)$(LOGDIR)
