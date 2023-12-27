//---------------------------------------------------------------------------
//  8 bit Long Division
//---------------------------------------------------------------------------
#include <vcl.h>
#include <tchar.h>
#pragma hdrstop
#pragma argsused

#include <iostream>
#include <iomanip>
#include <string>

#include "UnitMain.h"
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "8 bit Long Division\n\n";

	{
		byte x[] = {0x00, 0x01, 0x02, 0x03, 0x0F};
		byte y = 0x0F;

		for(int i = 0; i < sizeof(x)/sizeof(byte); i++)
		{
			DIV_QR z = __div_8_bit(x[i], y);

			std::cout << std::setfill('0') << std::hex << std::uppercase;

			if((z.quotient & z.reminder & 0xFF) == 0xFF)
			{
				std::cout << "x = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(x[i])
						  << " y = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(y)
						  << " | [overflow: division by zero]\n";
			}
			else
			{
				std::cout << "x = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(x[i])
						  << " y = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(y)
						  << " | quotient = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(z.quotient)
						  << " reminder = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(z.reminder) << "\n";
			}
		}
	}

	std::cout << std::endl;

	{
		byte x[] = {0x0F, 0x0C, 0x09, 0x03, 0x01, 0x00};
		byte y = 0x03;

		for(int i = 0; i < sizeof(x)/sizeof(byte); i++)
		{
			DIV_QR z = __div_8_bit(x[i], y);

			if((z.quotient & z.reminder & 0xFF) == 0xFF)
			{
				std::cout << "x = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(x[i])
						  << " y = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(y)
						  << " | [overflow: division by zero]\n";
			}
			else
			{
				std::cout << "x = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(x[i])
						  << " y = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(y)
						  << " | quotient = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(z.quotient)
						  << " reminder = "
						  << std::setfill('0') << std::hex << std::uppercase << std::setw(2)
						  << static_cast<int>(z.reminder) << "\n";
			}
		}
	}

	std::cout << std::endl;

	system("pause");
	return 0;
}
//------------------------------------------------------------------------------
//  8 bit Long Division
//  Machine Implementation
DIV_QR __div_8_bit(byte x, byte y)
//	Computes the quotient and reminder of division of the dividend x by the divisor y
//  https://en.wikipedia.org/wiki/Euclidean_division
//  Result:
//  - AH, quotient
//  - AL, reminder
//  If overflow (division by zero), AH = AL = 0xFF
{
	DIV_QR result;

	if(y == 0)
	{   //  Division by zero
		//  Set overflow
		result.quotient = 0xFF;
		result.reminder = 0xFF;
	}
	else
	{
		__asm
		{
				xor AX, AX      // AH - quotient; AL - reminder
				movzx DX, [x]   // DX - dividend
				mov CL, [y]     // CL - divisor
				mov BL, 8       // BL - counter

		L_LOOP: shl AL, 1       // set the next bit of the quotient to 0
				shl DX, 1
				cmp DH, CL
				js L_NXT

				sub DH, CL      // DH - partial dividend
				or AL, 0x01     // set the next bit of the quotient to 1

		L_NXT:  dec BL
				jnz L_LOOP

				mov AH, DH
				mov [result], AX
		}
	}

//	When using the classic Borland 32 bit compiler,
//	the result is returned implicitly through register AX
//	and the intermediate buffer variable result is optional,
//	but of course it is not wrong to use it either.
   return result;
}
//------------------------------------------------------------------------------

