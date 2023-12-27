//---------------------------------------------------------------------------
#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
using UINT = unsigned int;

union ULL
{
	struct
	{
		UINT lo;
		UINT hi;
	} dw;   				// Double Word part (2 x 32 bit)
	unsigned long long qw;	//   Quad Word part (1 x 64 bit)
};

struct DIV_T
{
	UINT quot;      		// 0xFFFFFFFF if overflow
	UINT rem;				// 0xFFFFFFFF if overflow
};

// 32 bit division
DIV_T div(const UINT& dividend, const UINT& divisor);
//---------------------------------------------------------------------------
#endif
