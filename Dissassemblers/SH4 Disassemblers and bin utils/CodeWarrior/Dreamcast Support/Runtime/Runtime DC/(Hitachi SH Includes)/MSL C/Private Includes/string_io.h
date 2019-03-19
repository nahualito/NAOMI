/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:44 PM                                   $ 
 *  $Revision:: 10                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	string_io.h
 */

#ifndef __string_io__
#define __string_io__

#include <ansi_parms.h>          /*hh 971206  this header should be first*/
#include <cstdio>                /*hh 971206  namespace support*/

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus          /*hh 971206  namespace support*/
	extern "C" {
#endif

int		__open_string_file(__std()FILE * file, char * str, __std()size_t n, int io_state);

int		__read_string		 (__std()__file_handle handle, unsigned char * buffer, __std()size_t * count, __std()__idle_proc idle_proc);
int		__write_string	 (__std()__file_handle handle, unsigned char * buffer, __std()size_t * count, __std()__idle_proc idle_proc);
int		__close_string	 (__std()__file_handle handle);

#ifdef __cplusplus          /*hh 971206  namespace support*/
	}
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif
/*     Change record
 *hh 971206  namespace support
*/
