/*
 *	ansi_prefix.SH_bare.h
 *	
 *		Copyright © 1997 Metrowerks, Inc.
 *		All rights reserved.
 */

#ifndef __ansi_prefix__
#define __ansi_prefix__
#define __MODENALIB__

#include <os_enum.h>
#include "IDT_config.h"

/*
	Processor family
*/
#ifndef __SH__
	#define __SH__
#endif /* __SH__ */

#ifndef __dest_os
	#define __dest_os  	__sh_bare
#endif /* __dest_os */

#if defined( __SH3__ )
	#define _No_Floating_Point	/* Comment out when fp emulation works. */
	#define _No_Floating_Point_Regs
#endif

	/* the following are OS services that aren't available */
#define _No_Time_OS_Support
#define _No_Alloc_OS_Support
//#define _No_Disk_File_OS_Support	/* modena needs file i/o */

	/* uncomment _No_Console if you do not want to	*/
	/* write and read to a console window.  		*/
//#define _No_Console

#ifndef _No_Console
	/* the serial UART library has unbuffered IO;	*/
	/* comment out the following line if you are 	*/
	/* either not using the serial UART library or 	*/
	/* if your OS has buffered IO.					*/
#define _Unbuffered_Console
#endif

//#define TARGET_LITTLE_ENDIAN 	/* unused */
#define TARGET_HEAP_ALIGNMENT	8
//#define TARGET_HEAP_ALIGNMENT	16

#define NEWMODE NEWMODE_MALLOC		//	always use malloc for new

#endif

#if __option( unsigned_char )
#define	__CHAR_IS_UNSIGNED__
#else
#define __CHAR_IS_SIGNED__
#endif
#define	__CHAR_IS_8BIT__
#define	__SHORT_IS_16BIT__
#define	__INT_IS_32BIT__
#define	__ENUM_IS_32BIT__
#define	__ENUM_IS_SIGNED__
#define	__LONG_IS_32BIT__
#define	__LONG_LONG_IS_32BIT__
#define	__FLOAT_IS_IEEE32__
#define	__DOUBLE_IS_IEEE64__
#define	__LONG_DOUBLE_IS_IEEE64__
#define	__LONG_LONG_DOUBLE_IS_IEEE64__
#define	__SIZE_T_IS_UINT__
#define	__PTRDIFF_T_IS_LONG__

#if ( ! __option( wchar_type ))
#define __NO_WIDE_CHAR
#endif

/*  Change Record
 *	980915	as	Adapted from DSP version.
 *	980929	as	Changed defines to be SH3 and SH4 specific.
 */


