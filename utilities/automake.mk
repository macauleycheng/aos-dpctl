bin_PROGRAMS += \
	utilities/dpctl


utilities_dpctl_SOURCES = utilities/dpctl.c
utilities_dpctl_LDADD = lib/libopenflow.a oflib/liboflib.a oflib-exp/liboflib_exp.a $(FAULT_LIBS) $(SSL_LIBS)

