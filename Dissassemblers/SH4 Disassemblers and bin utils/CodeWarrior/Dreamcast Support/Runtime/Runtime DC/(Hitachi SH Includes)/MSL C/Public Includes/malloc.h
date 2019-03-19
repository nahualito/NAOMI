/*  Metrowerks Standard Library  Version 4.0  1998 August 10  */

/*  $Date:: 3/10/98 7:51 PM                                  $ 
 *  $Revision:: 8                                            $ 
 *  $NoKeywords: $ 
 *
 *		Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */
 
/*
 *	malloc.h
 *
 *		This file was built to correspond with the Visual C++ malloc.h
 */

#include <ansi_parms.h>
#include <size_t.h>

__declspec(naked) char * _alloca(__std()size_t size);

#define alloca _alloca

/*
hh 980727 added __std() modifier to size_t
*/
