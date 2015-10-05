
/* linms begine Debug function*/
#ifndef __LINMSDEBUG_H
#define __LINMSDEBUG_H
#include <stdio.h>

#if(AOS_DEBUG == 1)

#define linmsfn() printf("%s(%d)\n", __FUNCTION__, __LINE__)
#define linmsfnl() printf("%s:(%d)\n", __FUNCTION__, __LINE__)
#define linmsfns(...) printf("%s:(%d) ", __FUNCTION__, __LINE__); printf (__VA_ARGS__)
#define linmsroe(f) printf("%s: %s(%d)\nReturn On Error: %s\n", __FILE__, __FUNCTION__, __LINE__, #f)
#define linmspl() printf("%s: %s(%d)\n", __FILE__, __FUNCTION__, __LINE__)
#define linmsfail() printf("*FAIL at %s: %s(%d)\n", __FILE__, __FUNCTION__, __LINE__)


#define linmsfn_lu(a) printf("%s(%d) %s: %lu\n", __FUNCTION__, __LINE__, #a, a)
#define linmsfn_u(a) printf("%s(%d) %s: %u\n", __FUNCTION__, __LINE__, #a, a)
#define linmsfn_X(a) printf("%s(%d) %s: %X\n", __FUNCTION__, __LINE__, #a, a)
#define linmsfn_s(a) printf("%s(%d) %s: %s\n", __FUNCTION__, __LINE__, #a, a)
#define linmsfn_i(a) printf("%s(%d) %s: %d\n", __FUNCTION__, __LINE__, #a, a)
#define linmsfn_ld(a) printf("%s(%d) %s: %ld\n", __FUNCTION__, __LINE__, #a, a)
#define linmsfn_b(a) printf("%s(%d) %s: %s\n", __FUNCTION__, __LINE__, #a, a?"TRUE":"FALSE")


#define linmsllu(a) printf("%s: %llu\n", #a, a)
#define linmslu(a) printf("%s: %lu\n", #a, a)
#define linmsu(a) printf("%s: %u\n", #a, a)
#define linmsX(a) printf("%s: %X\n", #a, a)
#define linmss(a) printf("%s: %s\n", #a, a)
#define linmsi(a) printf("%s: %d\n", #a, a)
#define linmsld(a) printf("%s: %ld\n", #a, a)
#define linmsb(a) printf("%s: %s\n", #a, a?"TRUE":"FALSE")
#define linmspf(...) printf (__VA_ARGS__)
#define linmsportlt(a, nb) {int i=0; printf("%s (Little Endian) start from 0\n", #a); for(i=0; i<nb; i++){ int j=7;printf("  ");for(j = 7; j >= 0; j--) { putchar('0' + ((a[i] >> j) & 1));}printf("\n");}}
#define linmsportbg(a, nb) {int i=0; printf("%s (Big Endian) start from 0 \n", #a); for(i=0; i<nb; i++) {int j=0;printf("  ");for(j = 0; j < nb; j++){putchar('0' + ((a[i] >> j) & 1));}printf("\n");}}
#define linmsport(a, nb) { int i=0; printf("%s (Unknown Endian) start from 0\n", #a);for(i=0; i<nb; i++) {int j=0;printf("  ");for(j = 0; j < nb; j++){ putchar('0' + ((a[i] >> j) & 1)); }printf("\n");}}
#define linmspuport(list,cnt) {int i=0;for(i=0;i<cnt;i++) printf("%u/%u ", list[i].unit, list[i].port);}
#define linmsfalportlist(pl) {int i=0;for(i=0;i<pl.nr_port;i++){printf("%u/%u ", pl.port[i].dev_id, pl.port[i].port_id);} printf("\n");}
#define linmsIPTo4D(ip)      (ip) >> 24 & 0x00FF, (ip) >> 16 & 0x00FF, (ip) >> 8 & 0x00FF, (ip) >> 0 & 0x00FF
#define linmsMACTo6D(mac) (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2], (unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5]
#define linmsmac(mac) printf("%s: %.2X-%.2X-%.2X-%.2X-%.2X-%.2X\n", #mac, (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2], (unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5])
#define linmsip(ip) printf("%s: %lu.%lu.%lu.%lu\n", #ip, linmsIPTo4D(ip))
#define linmsipv6(ip6) printf("%s: %2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x:%2.2x%2.2x\n", #ip6, (unsigned char)ip6[0], (unsigned char)ip6[1], (unsigned char)ip6[2], (unsigned char)ip6[3], (unsigned char)ip6[4], (unsigned char)ip6[5], (unsigned char)ip6[6], (unsigned char)ip6[7], (unsigned char)ip6[8], (unsigned char)ip6[9], (unsigned char)ip6[10], (unsigned char)ip6[11], (unsigned char)ip6[12], (unsigned char)ip6[13], (unsigned char)ip6[14], (unsigned char)ip6[15])
#define linmsdumpmem(tbuf, len) \
{\
    int i, j, k, l;\
    printf("      0       7 8      15 16     23 24     31\n");\
    printf("      |       | |       | |       | |       |\n");\
    for(i=0; i<len;)\
    {\
        printf("%4.4X  ", i);\
        for(j=0; j<4 && i<len;j++)\
        {\
            for(k=0; k<2 && i<len; k++)\
            {\
                for(l=0; l<2 && i<len; l++, i++)\
                {\
                    printf("%2.2X", (tbuf)[i]);\
                }\
                if(k==0)\
                    printf("-");\
            }\
            printf(" ");\
        }\
        printf("\n");\
    }\
}
#define linmsX0(a) linmsX0n(a, sizeof(a)*8)
#define linmsX0n(a, nb)  \
{\
	int i=0; \
	printf("%s 0x ", #a); \
	for(i=nb-1; i>=0; i--) \
	{\
		if(i!=nb-1 && (i+1)%4 == 0) \
			printf(" ");\
		printf("%d", a&(1<<i)?1:0);\
	}\
	printf(": "); \
	int prev=-1;\
	int pprev=-1;\
	for(i=0; i<nb; i++)\
	{\
		if(a&(1<<i))\
		{\
			if(i==prev+1)\
			{\
				if(pprev < 0)\
				{\
					pprev = prev;	\
				}\
			}\
			else\
			{\
				if(prev >= 0) \
				{ \
					if(pprev >= 0)\
					{\
						printf("%u-%u ", pprev, prev);	\
						pprev = -1;\
						prev = -1;\
					}\
					else\
					{\
						printf("%u ", prev);		\
					}\
				}\
			}\
			prev = i;\
		} \
	}\
	if(prev >= 0) \
    { \
        if(pprev >= 0)\
        {\
            printf("%u-%u ", pprev, prev);	\
            pprev = -1;\
            prev = -1;\
        }\
        else\
        {\
            printf("%u ", prev);		\
        }\
    }\
	printf("\n");\
}

#define linmsDumpBCMPortBitMap(pbm)\
{\
    printf("%s: \n", #pbm);\
    int i = 0;\
    for(i=0; i<5; i++)\
    {\
        printf("pbits[%d]: %8X\n", i, (unsigned int)pbm.pbits[i]);\
    }\
    printf("\n");\
}


#define linms_print_bcm_err_r_bcm \
do												\
{												\
	if (BCM_E_NONE != rv)						\
	{											\
		linmsfns("rv: %s\n", bcm_errmsg(rv));	\
		linmsfail();							\
		return rv;								\
	}											\
}while(0)

#define linms_print_bcm_err_r_l7false \
do												\
{												\
	if (BCM_E_NONE != rv)						\
	{											\
		linmsfns("rv: %s\n", bcm_errmsg(rv));	\
		linmsfail();							\
		return L7_FALSE;						\
	}											\
}while(0)

#define linms_print_bcm_err_r \
do												\
{												\
	if (BCM_E_NONE != rv)						\
	{											\
		linmsfns("rv: %s\n", bcm_errmsg(rv));	\
		linmsfail();							\
		return;									\
	}											\
}while(0)

#define linms_print_bcm_err \
do												\
{												\
	if (BCM_E_NONE != rv)						\
	{											\
		linmsfns("rv: %s\n", bcm_errmsg(rv));	\
		linmsfail();							\
	}											\
}while(0)

#else

#define linmsfn() printf("")
#define linmsfnl() printf("")
#define linmsfns(...) printf("")
#define linmsroe(f) printf("")
#define linmspl() printf("")
#define linmsfail() printf("")

#define linmsfn_lu(a) printf("")
#define linmsfn_u(a) printf("")
#define linmsfn_X(a) printf("")
#define linmsfn_s(a) printf("")
#define linmsfn_i(a) printf("")
#define linmsfn_ld(a) printf("")
#define linmsfn_b(a) printf("")

#define linmsllu(a) printf("")
#define linmslu(a) printf("")
#define linmsu(a) printf("")
#define linmsX(a) printf("")
#define linmss(a) printf("")
#define linmsi(a) printf("")
#define linmsld(a) printf("")
#define linmsb(a) printf("")
#define linmspf(...) printf("")
#define linmsportlt(a, nb) printf("")
#define linmsportbg(a, nb) printf("")
#define linmsport(a, nb) printf("")
#define linmspuport(list,cnt) printf("")
#define linmsfalportlist(pl) printf("")
#define linmsIPTo4D(ip) (ip) >> 24 & 0x00FF, (ip) >> 16 & 0x00FF, (ip) >> 8 & 0x00FF, (ip) >> 0 & 0x00FF
#define linmsMACTo6D(mac) (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2], (unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5]
#define linmsmac(mac) printf("")
#define linmsip(ip) printf("")
#define linmsipv6(ip6) printf("")
#define linmsdumpmem(tbuf, len) printf("")
#define linmsX0(a) linmsX0n(a, sizeof(a)*8)
#define linmsX0n(a, nb)  printf("")
#define linmsDumpBCMPortBitMap(pbm) printf("")
#define linms_print_bcm_err_r_bcm \
do                                              \
{                                               \
    if (BCM_E_NONE != rv)                       \
    {                                           \
        linmsfns("rv: %s\n", bcm_errmsg(rv));   \
        linmsfail();                            \
        return rv;                              \
    }                                           \
}while(0)

#define linms_print_bcm_err_r_l7false \
do                                              \
{                                               \
    if (BCM_E_NONE != rv)                       \
    {                                           \
        linmsfns("rv: %s\n", bcm_errmsg(rv));   \
        linmsfail();                            \
        return L7_FALSE;                        \
    }                                           \
}while(0)

#define linms_print_bcm_err_r \
do                                              \
{                                               \
    if (BCM_E_NONE != rv)                       \
    {                                           \
        linmsfns("rv: %s\n", bcm_errmsg(rv));   \
        linmsfail();                            \
        return;                                 \
    }                                           \
}while(0)

#define linms_print_bcm_err \
do                                              \
{                                               \
    if (BCM_E_NONE != rv)                       \
    {                                           \
        linmsfns("rv: %s\n", bcm_errmsg(rv));   \
        linmsfail();                            \
    }                                           \
}while(0)

#endif

#endif /* #ifndef __LINMSDEBUG_H */


