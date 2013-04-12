#ifndef _NCX_CORE_H_
#define _NCX_CORE_H_

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned char 	u_char;
typedef uintptr_t       ncx_uint_t; 
typedef intptr_t        ncx_int_t; 

#ifndef NCX_ALIGNMENT
#define NCX_ALIGNMENT   sizeof(unsigned long)    /* platform word */
#endif

#define ncx_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define ncx_align_ptr(p, a)                                                   \
	    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

#define ncx_memzero(buf, n)       (void) memset(buf, 0, n) 
#define ncx_memset(buf, c, n)     (void) memset(buf, c, n)

#endif
