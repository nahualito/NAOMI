/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:43 PM                                   $ 
 *  $Revision:: 10                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	buffer_io.h
 */

#ifndef __buffer_io__
#define __buffer_io__

#include <ansi_parms.h>                  /*hh 971206  this header must come first*/
#include <cstdio>                        /*hh 971206  namespace support*/

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus                  /*hh 971206  namespace support*/
	extern "C" {
#endif

enum {
	__align_buffer,
	__dont_align_buffer
};

void __convert_from_newlines(unsigned char * p, __std()size_t * n);
void __convert_to_newlines  (unsigned char * p, __std()size_t * n);

void	__prep_buffer (__std()FILE * file);	
int		__load_buffer (__std()FILE * file, __std()size_t * bytes_loaded, int alignment);
int		__flush_buffer(__std()FILE * file, __std()size_t * bytes_flushed);

#ifdef __cplusplus                  /*hh 971206  expanded _extern macro*/
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
