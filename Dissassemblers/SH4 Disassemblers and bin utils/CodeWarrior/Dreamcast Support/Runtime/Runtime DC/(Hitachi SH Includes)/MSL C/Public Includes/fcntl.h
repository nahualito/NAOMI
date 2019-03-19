/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:32 PM                                   $ 
 *  $Revision:: 11                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */
#include <ansi_parms.h>  /* m.f. 042898 */
#if !defined(__dest_os)               
  #error __dest_os undefined 
#endif                                            /*MW-mm 960927a*/
#if __dest_os == __mac_os
#	include <fcntl.mac.h>
#elif (__dest_os == __win32_os || __dest_os == __wince_os)
#	include <fcntl.win32.h>
#elif __dest_os == __powertv_os
#	include <fcntl.powertv.h>
#elif __dest_os == __be_os                         /* mm 970708 */
#	include <fcntl.be.h>                           /* mm 970708 */
#endif
/*     Change record
 * MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
 * mm 970708  Inserted Be changes
 * mf 980428  included ansi_parms.h and use #error instead of mac_os by default
 */
