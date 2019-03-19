#
#	linker.cmd
#
#	CodeWarrior for Dreamcast standard linker command file
#	Version.1.01
#
#	Metrowerks inc
#
#	1999.04.19	support ALIGNALL
#	1999.02.21	for 1.0.0
#	1999.01.21	for beta 1.5
#	1998.11.25	for beta 1
#	1999.03.21	for fc
#

$INCLUDE
{
	# These sections have to be included in an execute file.
	IP
	DSGLH
	DSGLE
	#	Only needed in C++
	#.exception
	# for version strings
	#	.rodata
	#	CSG
	# This section has to be included for SOFDEC.lib.
	#	PSGSFD01

	#	don't dead strip .data section
	#.data
}

$SEGMENT CODE_SG_IP 0x8C008000 R
{
	*(IP)
}

$SEGMENT DATA_SG_LH 0x8C010000 R
{
	ALIGNALL(0x08)
	__START_DSGLH	= .;
	*(DSGLH) 
	__END_DSGLH		= .;
	
	ALIGNALL(0x08)
	__START_DSGLE	= .;
	*(DSGLE)
	__END_DSGLE 	= .;
}

$SEGMENT CODE_USER R
{
	*(.text)
	*(P)
}

$SEGMENT CONST_USER R
{
	ALIGNALL(0x08)
	*(.rodata)
	ALIGNALL(0x08)
	*(C)
	ALIGNALL(0x20)
	*(C32)
}

$SEGMENT DATA_EXCPTION R
{
	# Include the exception table index. Only needed in C++
	ALIGN(0x4);
	*(.exception)
	ALIGN(0x4);
	*(.exceptlist)
}

$SEGMENT DATA_USER
{
	ALIGNALL(0x08)
	__START_D		= .;
	*(.data)
	ALIGNALL(0x08)
	*(D)
	__END_D 		= .;

	ALIGNALL(0x20)
	__START_D32		= .;
	*(D32)
	__END_D32		= .;

	__START_R		= .;
	__END_R			= .;
	__START_R32		= .;
	__END_R32		= .;
}

$SEGMENT CODE_SG R
{
	*(PSG)
}

$SEGMENT CONST_SG R
{
	ALIGNALL(0x08)
	*(CSG)
	ALIGNALL(0x20)
	*(CSG32)
}

$SEGMENT DATA_SG
{
	ALIGNALL(0x08)
	__START_DSG		= .;
	*(DSG)
	__END_DSG		= .;

	ALIGNALL(0x20)
	__START_DSG32	= .;
	*(DSG32)
	__END_DSG32		= .;

	__START_RSG		= .;
	__END_RSG		= .;
	__START_RSG32	= .;
	__END_RSG32		= .;
}

#	Ninja sections
#
#	$SEGMENT CODE_SG_NINJA R
#	{
#		PSGNJ00
#		PSGNJ01
#		PSGNJ02
#		PSGNJ03
#		PSGNJ04
#		PSGNJ05
#		PSGNJ06
#		PSGNJ07
#		PSGNJ08
#		PSGNJ09
#		PSGNJ10
#		PSGNJ11
#		PSGNJ12
#		PSGNJ13
#		PSGNJ14
#		PSGNJ15
#	}
#
#	$SEGMENT DATA_SG_NINJA
#	{
#		DSGNJ00
#		DSGNJ01
#		DSGNJ02
#		DSGNJ03
#		DSGNJ04
#		DSGNJ05
#		DSGNJ06
#		DSGNJ07
#		DSGNJ08
#		DSGNJ09
#		DSGNJ10
#		DSGNJ11
#		DSGNJ12
#		DSGNJ13
#		DSGNJ14
#		DSGNJ15
#	}

#	Middleware sections
#
#	$SEGMENT CODE_SG_MW R
#	{
#		PSGMW00
#		PSGMW01
#		PSGMW02
#		PSGMW03
#		PSGMW04
#		PSGMW05
#		PSGMW06
#		PSGMW07
#		PSGMW08
#		PSGMW09
#		PSGMW10
#		PSGMW11
#		PSGMW12
#		PSGMW13
#		PSGMW14
#		PSGMW15
#	}
#
#	$SEGMENT DATA_SG_MW
#	{
#		DSGMW00
#		DSGMW01
#		DSGMW02
#		DSGMW03
#		DSGMW04
#		DSGMW05
#		DSGMW06
#		DSGMW07
#		DSGMW08
#		DSGMW09
#		DSGMW10
#		DSGMW11
#		DSGMW12
#		DSGMW13
#		DSGMW14
#		DSGMW15
#	}

#	Sofdec sections
#
#	*** if you use SOFDEC.LIB, please remove "#" below. ***
#
#	$SEGMENT CODE_SG_SOFDEC R
#	{
#		__START_PSGSFD00	= .;
#		PSGSFD00
#		__END_PSGSFD00		= .;
#	
#		__START_PSGSFD01	= .;
#		PSGSFD01
#		__END_PSGSFD01		= .;
#	
#		__START_PSGSFD02	= .;
#		PSGSFD02
#		__END_PSGSFD02		= .;
#	
#		__START_PSGSFD03	= .;
#		PSGSFD03
#		__END_PSGSFD03		= .;
#	
#		__SIZE_PSGSFD00		= __END_PSGSFD00 - __START_PSGSFD00;
#		__SIZE_PSGSFD01		= __END_PSGSFD01 - __START_PSGSFD01;
#		__SIZE_PSGSFD02		= __END_PSGSFD02 - __START_PSGSFD02;
#		__SIZE_PSGSFD03		= __END_PSGSFD03 - __START_PSGSFD03;
#	}
#
#	$SEGMENT DATA_SG_SOFDEC
#	{
#		DSGSFD00
#		DSGSFD01
#		DSGSFD02
#		DSGSFD03
#	}

#	Reserved sections
#
#	$SEGMENT CODE_SG_RESERVED R
#	{
#		PSGRSV0
#		PSGRSV1
#		PSGRSV2
#		PSGRSV3
#	}
#
#	$SEGMENT DATA_SG_RESERVED
#	{
#		DSGRSV0
#		DSGRSV1
#		DSGRSV2
#		DSGRSV3
#	}

#	User Reserved sections
#
#	$SEGMENT CODE_USER_RESERVED R
#	{
#		PUSER0
#		PUSER1
#		PUSER2
#		PUSER3
#	}
#
#	$SEGMENT DATA_USER_RESERVED
#	{
#		DUSER0
#		DUSER1
#		DUSER2
#		DUSER3
#	}

#	C++ exception sections
#
#	*** For C++ runtime with exceptions ACTIVATED, please remove "#" below. ***
#
#$SEGMENT DATA_EXCPT
#{
#    *(.exception)
#    *(.exceptlist)
#}

$SEGMENT BSS_USER
{
	ALIGNALL(0x08)
	__START_B 		= .;
	*(.bss)
	ALIGNALL(0x08)
	*(B)
	__END_B			= .;

	ALIGNALL(0x20)
	__START_B32		= .;
	*(B32)
	__END_B32		= .;
}

$SEGMENT BSS_SG
{
	ALIGNALL(0x08)
	__START_BSG		= .;
	*(BSG)
	__END_BSG		= .;

	ALIGNALL(0x20)
	__START_BSG32	= .; 
	*(BSG32)
	__END_BSG32		= .;
}
