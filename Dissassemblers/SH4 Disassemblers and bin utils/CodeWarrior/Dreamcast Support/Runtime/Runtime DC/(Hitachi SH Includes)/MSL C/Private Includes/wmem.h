/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:44 PM                                   $ 
 *  $Revision:: 3                                            $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	mem_funcs.h
 */
 
#ifndef __wmem_funcs__
#define __wmem_funcs__

#include <ansi_parms.h>                 /* mm 970905*/
#include <mem_funcs.h>
#include <cstddef>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus
	#ifdef _MSL_USING_NAMESPACE
		namespace std {
	#endif
	extern "C" {
#endif

/* extern prototypes */

void * 	(wmemcpy)(void * dst, const void * src, size_t n);
void * 	(wmemmove)(void * dst, const void * src, size_t n);
void * 	wmemset(void * dst, int val, size_t n);
void * 	wmemchr(const void * src, int val, size_t n);
int 	wmemcmp(const void * src1, const void * src2, size_t n);

#ifdef __cplusplus
	}
	#ifdef _MSL_USING_NAMESPACE
		}
	#endif
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif	/* #ifndef __wmem_funcs__ */


/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 */
