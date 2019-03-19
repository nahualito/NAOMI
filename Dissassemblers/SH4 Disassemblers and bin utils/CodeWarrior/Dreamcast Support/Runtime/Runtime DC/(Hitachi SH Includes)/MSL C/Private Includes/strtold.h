/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:44 PM                                   $ 
 *  $Revision:: 11                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	strtod.h
 */
 
#ifndef __strtod__
#define __strtod__

#include <ansi_parms.h>
#include <cstdio>               /* mm 970905 */ /*hh 971206  namespace support*/

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus          /*hh 971206  namespace support*/
	extern "C" {
#endif

extern long double __strtold(int		max_width,
														 __std()FILE	* input_stream,
														 int	* chars_scanned,
														 int	* overflow);

#ifdef __cplusplus          /*hh 971206  namespace support*/
	}
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif
/*     Change record
 * mm 970905  added include of stdio.h to allow this header to be included first.
 *hh 971206  namespace support
 */
