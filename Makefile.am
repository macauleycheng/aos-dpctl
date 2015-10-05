# The goal of -Wno-syntax here is just to suppress the Automake warning
# about overriding distdir, below.
AUTOMAKE_OPTIONS = foreign -Wno-syntax subdir-objects
ACLOCAL_AMFLAGS = -I m4
SUBDIRS =

AM_CPPFLAGS = $(SSL_CFLAGS) -g
AM_CPPFLAGS += -I $(top_srcdir)/include
AM_CPPFLAGS += -I $(top_srcdir)/lib

AM_CFLAGS = -Wstrict-prototypes


CLEANFILES =
DISTCLEANFILES =
EXTRA_DIST =
TESTS =
TESTS_ENVIRONMENT =
bin_PROGRAMS =
bin_SCRIPTS =
#dist_commands_DATA =
dist_man_MANS =
dist_pkgdata_SCRIPTS =
dist_sbin_SCRIPTS =
man_MANS =
noinst_HEADERS =
noinst_LIBRARIES =
noinst_PROGRAMS =
noinst_SCRIPTS =


include lib/automake.mk
include oflib/automake.mk
include oflib-exp/automake.mk
include utilities/automake.mk
include include/automake.mk

