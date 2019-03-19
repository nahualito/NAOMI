/*
	prefix.h

	CodeWarrior for Dreamcast standard prefix file
	Version.1.01

	Metrowerks inc

	1999.04.22	add sttic intializer/destructor
	1999.02.21	for 1.0.0
	1998.11.25	for beta 1
	1999.03.21	for	fc

*/

#define		__SHC__
#define		__SET4__
#define		__SET5__
#define		__KATANA__

/* For Kamui */
#define		_CLX_
#define		_CLX2_
#define     	_STRICT_UNION_

/* for compatibility with SHC (sg_sysrt.h) */
#define	syStartGlobalConstructor	__call_static_initializers
#define	syStartGlobalDestructor		__destroy_global_chain
