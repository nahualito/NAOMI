/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:44 PM                                   $ 
 *  $Revision:: 5                                            $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	strtoul.h
 */
 
#ifndef __wcstoul__
#define __wcstoul__

#include <ansi_parms.h>
#include <cstdio>          /*hh 971206  changed from stdio.h*/

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus          /*hh 971206  namespace support*/
	extern "C" {
#endif

extern unsigned long __wcstoul(int		base, 
															 int		max_width,
															 __std()FILE	* input_stream,
															 int	* chars_scanned,
															 int	* negative,
															 int	* overflow);

#ifdef __MSL_LONGLONG_SUPPORT__              /*mm 970110*/
extern unsigned long long __wcstoull(int		base, 
															 int		max_width,
															 __std()FILE	* input_stream,
															 int	* chars_scanned,
															 int	* negative,
															 int	* overflow);
#endif   /*__MSL_LONGLONG_SUPPORT__*/        /*mm 970110*/

#ifdef __cplusplus          /*hh 971206  expanded __extern macro*/
	}
#endif

#ifdef __cplusplus
	#ifdef _MSL_USING_NAMESPACE
		namespace std {
	#endif
	extern "C" {
#endif

/* prototypes */

unsigned long 		wcstoul (const wchar_t * str, wchar_t ** end, int base);
unsigned long long 	wcstoull(const wchar_t * str, wchar_t ** end, int base);
long 				wcstol  (const wchar_t * str, wchar_t ** end, int base);
long long 			wcstoll (const wchar_t * str, wchar_t ** end, int base);
int 				watoi   (const wchar_t * str);
long 				watol   (const wchar_t * str);

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

#endif /* #ifndef __wcstoul__ */

/*     Change record
mm 970110  Changed wrappers for long long support
hh 971206  namespace support added
blc 980324 fixed prototypes for C9X conformance
*/
