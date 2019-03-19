#define PROM_ENTRY(x)		(0xbfc00000+((x)*8))
#define PROM_RESET			PROM_ENTRY(0)
#define PROM_RESTART		PROM_ENTRY(2)
#define PROM_REINIT			PROM_ENTRY(3)
#define PROM_OPEN			PROM_ENTRY(6)
#define PROM_READ			PROM_ENTRY(7)
#define PROM_WRITE			PROM_ENTRY(8)
#define PROM_IOCTL			PROM_ENTRY(9)
#define PROM_CLOSE			PROM_ENTRY(10)
#define PROM_GETCHAR		PROM_ENTRY(11)
#define PROM_PUTCHAR		PROM_ENTRY(12)
#define PROM_SHOWCHAR		PROM_ENTRY(13)
#define PROM_GETS			PROM_ENTRY(14)
#define PROM_PUTS			PROM_ENTRY(15)
#define PROM_PRINTF			PROM_ENTRY(16)
#define PROM_EXIT			PROM_ENTRY(17)
#define PROM_RFILEINIT		PROM_ENTRY(18)
#define PROM_ROPEN			PROM_ENTRY(19)
#define PROM_RCLOSE			PROM_ENTRY(20)
#define PROM_RREAD			PROM_ENTRY(21)
#define PROM_RWRITE			PROM_ENTRY(22)
#define PROM_RLSEEK			PROM_ENTRY(23)
#define PROM_RPRINTF		PROM_ENTRY(24)
#define PROM_RGETS			PROM_ENTRY(25)
#define PROM_FLUSH_CACHE	PROM_ENTRY(28)
#define PROM_CLEAR_CACHE	PROM_ENTRY(29)
#define PROM_SETJMP			PROM_ENTRY(30)
#define PROM_LONGJMP		PROM_ENTRY(31)
#define PROM_EXC_UTLB_CODE	PROM_ENTRY(32)
#define PROM_SPRINTF		PROM_ENTRY(34)
#define PROM_ATOB			PROM_ENTRY(35)
#define PROM_STRCMP			PROM_ENTRY(36)
#define PROM_STRLEN			PROM_ENTRY(37)
#define PROM_STRCPY			PROM_ENTRY(38)
#define PROM_STRCAT			PROM_ENTRY(39)
#define PROM_CLI			PROM_ENTRY(40)
#define PROM_GET_RANGE		PROM_ENTRY(41)
#define PROM_TOKENIZE		PROM_ENTRY(42)
#define PROM_TIMER_START	PROM_ENTRY(44)
#define PROM_TIMER_STOP		PROM_ENTRY(45)
#define PROM_EXC_NORM_CODE	PROM_ENTRY(48)