/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:34 PM                                   $ 
 *  $Revision:: 10                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */
#include <ansi_parms.h>  /* m.f. 042898 */
#if !defined(__dest_os)               
  #error __dest_os undefined 
#endif                                              /*MW-mm 960927a*/

#if __dest_os == __mac_os

#include <utime.mac.h>

#elif __dest_os == __win32_os

#include <utime.win32.h>

#elif __dest_os == __powertv_os

#include <utime.powertv.h>

#endif
/*     Change record
 * MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
 * mf 980428  included ansi_parms.h and use #error instead of mac_os by default
*/
