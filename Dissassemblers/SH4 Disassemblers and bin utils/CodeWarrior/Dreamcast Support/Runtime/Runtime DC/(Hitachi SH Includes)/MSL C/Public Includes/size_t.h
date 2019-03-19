/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:33 PM                                   $ 
 *  $Revision:: 14                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	size_t.h
 */
 
#ifndef __size_t__
#define __size_t__

#include <ansi_parms.h>                 /* mm 970905*/

#ifdef __cplusplus      /* hh  971206 */
	#ifdef _MSL_USING_NAMESPACE
		namespace std {
	#endif
	extern "C" {
#endif

#if __dest_os == __win32_os || __MOTO__  || __dest_os == __wince_os
	#define _SIZE_T_DEFINED
	typedef unsigned int	size_t;
#else
	typedef unsigned long	size_t;
#endif

#ifdef __cplusplus      /* hh  971206 */
	}
	#ifdef _MSL_USING_NAMESPACE
		}
	#endif
#endif

#endif /* __size_t__ */

/*     Change record
 * mm 970905  added include of ansi_parms.h to avoid need for prefix file
 * hh  971206   added namespace support.
 * mf  980507 added typedef of size_t for wince
 */
