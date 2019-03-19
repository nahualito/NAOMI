/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:32 PM                                   $ 
 *  $Revision:: 12                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	div_t.h
 */
 
#ifndef __div_t__
#define __div_t__

#include <ansi_parms.h>                 /* mm 970905*/

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus      /* hh  971206 */
	extern "C" {
#endif

typedef struct {
	int	quot;
	int	rem;
} div_t;

typedef struct {
	long	quot;
	long	rem;
} ldiv_t;


#ifdef __MSL_LONGLONG_SUPPORT__ 	/* as 981014 */
/* hh 980122 added */
typedef struct {
	long long	quot;
	long long	rem;
} lldiv_t;
#endif

#ifdef __cplusplus      /* hh  971206 */
	}
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif

/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 * hh  971206 added extern "C" (think maintenance).
 * hh 980122 added long long support
 * as 981014 bracketed long long support 
*/
