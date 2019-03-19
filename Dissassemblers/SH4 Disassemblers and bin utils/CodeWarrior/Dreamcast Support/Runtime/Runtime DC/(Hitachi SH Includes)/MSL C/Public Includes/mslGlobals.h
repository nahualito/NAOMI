/*  Metrowerks Standard Library  Version 2.4  1998 March 10  */

/*  $Date:: 6/5/98 2:33 PM                                   $ 
 *  $Revision:: 3                                            $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */
 
/*
 *	mslGlobals.h
 */

/*
	The purpose of this file is to set up those aspects of the environment
	that are global to both the C and C++ library.  The top of the dependency
	tree for the C library is ansi_parms.h.  The top for the C++ library is
	mcompile.h.  In order to avoid duplicating code in these two files, this
	file will be included by both ansi_parms.h and mcompile.h.  Only put stuff
	in here that otherwise would have to have been duplicated in ansi_parms.h
	and mcompile.h.
*/

#ifndef __mslGlobals_h
#define __mslGlobals_h

#if defined(__MC68K__) || defined(__POWERPC__)
	#include <ansi_prefix.mac.h>
#elif defined(__INTEL__)
	#if !defined(UNDER_CE)
		#include <ansi_prefix.Win32.h>
	#endif
#elif defined(__MIPS__)
	#include <ansi_prefix.MIPS_bare.h>
#elif defined( __SH3__ ) || defined( __SH4__ )
	#include <ansi_prefix.SH_bare.h>
#elif defined(__MCORE__)
	#include <ansi_prefix.MCORE_EABI_bare.h>
#else
	#error mslGlobals.h could not include prefix file
#endif

/* Turn on and off namespace std here */
#if defined(__cplusplus) && __embedded_cplusplus == 0
//	#define _MSL_USING_NAMESPACE	// 990409 AS msl c++ is built on hitachi c, they dont use namespaces yet..
	/* Turn on support for wchar_t as a built in type */
	/* #pragma wchar_type on */   /*  vss  not implemented yet  */
#endif

#endif

/* Change Record
 * hh 980120 created
 * cw 980825 added prefix file entry for SH
 * as 980909 added prefix file entry for MCORE
*/
