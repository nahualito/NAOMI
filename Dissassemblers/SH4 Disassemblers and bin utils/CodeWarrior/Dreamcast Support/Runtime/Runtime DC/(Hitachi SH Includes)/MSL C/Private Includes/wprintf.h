/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:44 PM                                   $ 
 *  $Revision:: 3                                            $ 
 *  $NoKeywords: $ 
 *
 *		Copyright � 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	wchar_io.h
 */

#ifndef __fwprintf_h__
#define __fwprintf_h__

#include <ansi_parms.h>
#include <cstdio>

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

int 	fwprintf(FILE * file, const wchar_t * format, ...);
int 	wprintf(const wchar_t * format, ...);
int 	swprintf(wchar_t * s, size_t n, const wchar_t * format, ...);
int 	vfwprintf(FILE * file, const wchar_t * format_str, va_list arg);
int 	vswprintf(wchar_t * s, size_t n, const wchar_t * format, va_list arg);
int 	vwprintf(const wchar_t * format, va_list arg);

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

#endif /* ifndef __fwprintf_h__ */


/*     Change record
*/
