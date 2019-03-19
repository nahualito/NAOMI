/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 6/18/98 12:28 PM                                 $ 
 *  $Revision:: 11                                           $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */

/*
 *	utility.h       // hh 971207 Changed filename from utility to utility.h
 */

#ifndef  _UTILITY_H           // hh 971207 added standard include guards
#define  _UTILITY_H

#include <utility>

#ifdef MSIPL_USING_NAMESPACE     // hh 971207 Added backward compatibility
	using namespace std;
	using namespace std::rel_ops;
	namespace std { using namespace rel_ops; }
#endif

#endif
/*     Change record
// hh 971207 Changed filename from utility to utility.h
// hh 971207 added standard include guards
// hh 971207 Added backward compatibility
*/
