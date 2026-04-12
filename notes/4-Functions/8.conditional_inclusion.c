// Make sure contents of `hdr.h` are included only once
#if !defined(HDR)
#define HDR
/* contents of hdr.h */
#endif

// Alternative form
#ifndef HDR
#define HDR
/* contents of hdr.h */
#endif

// Decide which version of a header to include
#if SYSTEM == SYSV
    #define HDR "sysv.h"
#elif SYSTEM == BSD
    #define HDR "bsd.h"
#elif SYSTEM == MSDOS
    #define HDR "msdos.h"
#else
    #define HDR "default.h"
#endif
#include HDR
