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
//---------------------------------------------------------------------------
#endif
