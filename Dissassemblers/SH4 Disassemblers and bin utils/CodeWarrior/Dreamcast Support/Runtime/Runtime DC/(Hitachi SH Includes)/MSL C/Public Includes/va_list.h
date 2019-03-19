/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:34 PM                                   $ 
 *  $Revision:: 12                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	va_list.h
 */
 
#ifndef __va_list__
#define __va_list__

#include <ansi_parms.h>                 /* mm 970905*/

#ifdef __cplusplus              /* hh  971206  */
	#ifdef _MSL_USING_NAMESPACE
		namespace std {
	#endif
	extern "C" {
#endif

typedef char * va_list;

#ifdef __cplusplus             /* hh  971206  */
	}
	#ifdef _MSL_USING_NAMESPACE
		}
	#endif
#endif

#endif /* __va_list__ */

/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 * hh 971206  added namespace support.  Is the extern "C" necessary?  Probably not.
 */
