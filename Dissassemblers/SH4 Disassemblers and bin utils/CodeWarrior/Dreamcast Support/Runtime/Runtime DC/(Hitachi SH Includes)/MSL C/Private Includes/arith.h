/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:43 PM                                   $ 
 *  $Revision:: 11                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	arith.h
 */
 
#ifndef __arith__
#define __arith__

#include <ansi_parms.h>
#include <div_t.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus          /*hh 971206  expanded __extern macro*/
	extern "C" {
#endif

int			__add (int  * x, int  y);
int			__ladd(long * x, long y);
int __lladd(long long * x, long long y);

int			__mul (int  * x, int  y);
int			__lmul(long * x, long y);
int __llmul(long long * x, long long y);

div_t		__div (int  x, int  y);
ldiv_t	__ldiv(long x, long y);
lldiv_t __lldiv(long long x, long long y);

#ifndef __MOTO__
int			__mod (int  x, int  y);
long		__lmod(long x, long y);
long long __llmod(long long x, long long y);
#endif

#ifdef __cplusplus          /*hh 971206  expanded __extern macro*/
	}
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif
/*     Change record
961221 bkoz lien 30 added mmoss's change
hh 971206  expanded __extern macro
*/
