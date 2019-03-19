/*  Metrowerks Standard Library  Version 2.4  1998 March 10  */

/*  $Date:: 6/5/98 2:43 PM                                   $ 
 *  $Revision:: 10                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	char_io.h
 */

#ifndef __char_io__
#define __char_io__

#include <ansi_parms.h>                  /*hh 971206  this header must come first*/
#include <cstdio>                        /*hh 971206  namespace support*/

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus                  /*hh 971206  namespace support*/
	extern "C" {
#endif

int	__ungotten(__std()FILE * file);

#ifdef __cplusplus                  /*hh 971206  expanded _extern macro*/
	}
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#if defined( __SH3__ )
int __syscall(int, int);			/*as 980930	 output for sh and partner */
#define FCT_OUTPUT 0x0000FE00		/*as 980930	 output for sh and partner */
#elif defined( __SH4__ )
extern int _write( int filedes, char * buf, int bfsz );
#endif /* __SH3__ */
#endif /* __char_io */

/*     Change record
 *	971206	hh	namespace support
 *	980930	AS	added sh specific defines.
*/
