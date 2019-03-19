
/* 
 *	Software Floating-Point Arithmetic Support for SH Targets
 *
 *	Currently sh4 has hardware floating point via set5 box
 *	and sh3 has no floating point but will have emulation.
 */
 
//#ifndef _No_Floating_Point

float _f_add(float, float);
float _f_sub(float, float);
float _f_mul(float, float);
float _f_div(float, float);
int _f_cmp(float, float);
unsigned long _f_ftou(float);
float _f_utof(unsigned long);
long _f_ftoi(float);
float _f_itof(long);
double _f_ftod(float);
double _d_add(double d1, double d2);
double _d_sub(double d1, double d2);
double _d_mul(double d1, double d2);
double _d_div(double d1, double d2);
int _d_cmp(double, double);
unsigned long _d_dtou(double);
double _d_utod(unsigned long);
long _d_dtoi(double);
double _d_itod(long);
float _d_dtof(double);
double _d_neg(double);

float _f_add(float, float)
{
	return 0;
}

float _f_sub(float, float)
{
	return 0;
}

float _f_mul(float, float)
{
	return 0;
}

float _f_div(float, float)
{
	return 0;
}

int _f_cmp(float, float)
{
	return 0;
}

unsigned long _f_ftou(float)
{
	return 0;
}

float _f_utof(unsigned long)
{
	return 0;
}

long _f_ftoi(float)
{
	return 0;
}

float _f_itof(long)
{
	return 0;
}

double _f_ftod(float)
{
	return 0;
}

double _d_add(double d1, double d2)
{
#pragma unused(d1, d2)
	return 0;
}

double _d_sub(double d1, double d2)
{
#pragma unused(d1, d2)
	return 0;
}

double _d_mul(double d1, double d2)
{
#pragma unused(d1, d2)
	return 0;
}

double _d_div(double d1, double d2)
{
#pragma unused(d1, d2)
	return 0;
}

int _d_cmp(double, double)
{
	return 0;
}

unsigned long _d_dtou(double)
{
	return 0;
}

double _d_utod(unsigned long)
{
	return 0;
}

long _d_dtoi(double)
{
	return 0;
}

double _d_itod(long)
{
	return 0;
}

float _d_dtof(double)
{
	return 0;
}

double _d_neg(double)
{
	return 0;
}

//#endif	/* _No_Floating_Point */