//---------------------------------------------------------------------------
//  32 bit Long Machine Division
//---------------------------------------------------------------------------
#include <vcl.h>
#include <tchar.h>
#pragma hdrstop
#pragma argsused

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

#include "UnitMain.h"
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "32 bit Long Machine Division\n\n";

	UINT x[] = {0x00, 0x01, 0x02, 0x0F, 0xFF, 0xFFF, 0xFFFFFFFF};
	UINT y[] = {0x1, 0xA, 0xF, 0x3F, 0xFF, 0xFFF};

	for(auto i = 0; i < sizeof(x)/sizeof(UINT); i++)
	{
		for(auto j = 0; j < sizeof(y)/sizeof(UINT); j++)
		{
			DIV_T z = div(x[i], y[j]);

			if((z.quot == std::numeric_limits<UINT>::max()) && (z.rem == std::numeric_limits<UINT>::max()))
			{   //  Overflow
				std::cout << "x = "
						  << std::hex << std::uppercase << std::setw(8)
						  << x[i]
						  << " y = "
						  << std::setfill(' ') << std::hex << std::uppercase << std::setw(8)
						  << y[j]
						  << " | [overflow: division by zero]"
						  << std::endl;
			}
			else
			{
				std::cout << "x = "
						  << std::hex << std::uppercase << std::setw(8)
						  << x[i]
						  << " y = "
						  << std::setfill(' ') << std::hex << std::uppercase << std::setw(8)
						  << y[j]
						  << " | quotient = "
						  << std::setfill(' ') << std::hex << std::uppercase << std::setw(8)
						  << z.quot
						  << " reminder = "
						  << std::setfill(' ') << std::hex << std::uppercase << std::setw(8)
						  << z.rem
						  << std::endl;
			}
		}

        std::cout << std::endl;
	}

	std::cout << std::endl;

	system("pause");
	return 0;
}
//------------------------------------------------------------------------------
//  32 bit Long Machine Division
//  C++ Implementation
DIV_T div(const UINT& dividend, const UINT& divisor)
//	Computes the quotient and reminder of division of the dividend by the divisor
{
	DIV_T result;

	if(divisor == 0)
	{   //  Division by zero
		//  Set overflow
		result.quot = std::numeric_limits<UINT>::max();
		result.rem  = std::numeric_limits<UINT>::max();
	}
	else
	{
		// DX - dividend
		ULL DX; DX.dw.hi = 0; DX.dw.lo = dividend;

		// CL - divisor
		UINT CL = divisor;

		// AH - quotient
		UINT AH = 0;

		for(auto i = 0; i < std::numeric_limits<UINT>::digits; i++)
		{
			AH <<= 1;			//	clear the next bit of the quotient
			DX.qw <<= 1;        //  take the next MS bit of the dividend

			if(DX.dw.hi >= CL)
			{
				DX.dw.hi -= CL; //	DH - partial dividend
				AH |= 1;		//	set the next bit of the quotient
			}
		}

		result.quot = AH;       //  Final Quotient
		result.rem  = DX.dw.hi; //  Final Reminder
	}

   return result;
}
//------------------------------------------------------------------------------

