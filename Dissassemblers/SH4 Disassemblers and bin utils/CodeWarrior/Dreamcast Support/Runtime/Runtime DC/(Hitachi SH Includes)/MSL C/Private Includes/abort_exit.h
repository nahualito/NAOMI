/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:43 PM                                   $ 
 *  $Revision:: 11                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright � 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	abort_exit.h
 */

#ifndef __abort_exit__
#define __abort_exit__

#include <ansi_parms.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef __cplusplus        /*hh 971206  expanded __extern macro*/
	extern "C" {
#endif

extern void (* __stdio_exit)  (void);
extern void (* __console_exit)(void);

extern int	__aborting;

int		__atexit(void (* func)(void));
void	__exit(int status);

#if __dest_os == __be_os
	void	__setup_exit(void);
#else
	#define __setup_exit()
#endif

#if (__dest_os == __win32_os || __dest_os == __wince_os	)
void _CleanUpMSL();
#endif

#if __dest_os == __ppc_eabi
void _ExitProcess(void);													
#endif

#ifdef __cplusplus        /*hh 971206  expanded __extern macro*/
	}
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif
/*     Change record
hh 971206  expanded __extern macro
mf 980515  wince changes
*/
