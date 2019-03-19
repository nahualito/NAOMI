/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:44 PM                                   $ 
 *  $Revision:: 3                                            $ 
 *  $NoKeywords: $ 
 *
 *		Copyright � 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	mem_funcs.h
 */
 
#ifndef __wctrans_h__
#define __wctrans_h__

#include <ansi_parms.h>                 /* mm 970905*/
#include <cstring>

#include <cwchar>
#include <cwctype>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus               /*  hh  971206 */
	#ifdef _MSL_USING_NAMESPACE
		namespace std {
	#endif
	extern "C" {
#endif

typedef wchar_t wctrans_t;


/* extern prototypes */

wint_t 		towctrans(wint_t c, wctrans_t value);
wctrans_t 	wctrans(const char *name);

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

#endif	/* #ifndef __wctrans_h__ */


/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 */
