/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/5/98 2:33 PM                                   $ 
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

#include <unistd.mac.h>

#elif ( __dest_os == __win32_os || __dest_os == __wince_os)

#include <unistd.win32.h>

#elif __dest_os == __powertv_os

#include <unistd.powertv.h>


#endif
/*     Change record
MW-mm 960927a Inserted setting of __dest_os to __mac_os when not otherwise set.
 * mf 980428  included ansi_parms.h and use #error instead of mac_os by default
*/
