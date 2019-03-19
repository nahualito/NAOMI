/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:43 PM                                   $ 
 *  $Revision:: 12                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	lconv.h
 */
 
#ifndef __lconv__
#define __lconv__

#include <ansi_parms.h>                 /* mm 970905*/

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus           /*hh 971206  namespace support*/
	#ifdef _MSL_USING_NAMESPACE
		namespace std {
	#endif
	extern "C" {
#endif

extern struct lconv __lconv;

#ifdef __cplusplus          /*hh 971206  namespace support*/
	}
	#ifdef _MSL_USING_NAMESPACE
		}
	#endif
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif
/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 * hh 971206  namespace support
 */
