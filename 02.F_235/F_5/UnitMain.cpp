//---------------------------------------------------------------------------
//  Факторизация от вида к*(5^exp)
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>
//#include <stdio.h>

#include <iostream>
#include <iomanip>
//#include <chrono>
//#include <string>		// included to be able to put std::string into std::cout

#include "UnitMain.h"
//---------------------------------------------------------------------------
const DWORD BEG		= 0;
const DWORD N 		= 32;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Factorization as k*(5^exp)" << std::endl;
	#if defined __F_35_BE_MOD__
		std::cout << "[Branch Elimination Technique]" << std::endl;
	#elif defined __F_35_BE2_MOD__
		std::cout << "[Branch Elimination Technique 2]" << std::endl;
	#endif
	std::cout << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		int exp_5;
		DWORD k = f_5(i, exp_5);

		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << " " << std::dec << std::setw(3) << std::setfill(' ')
				  << k << "*(5^" << exp_5 << ")";

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
DWORD f_5(DWORD src, int& exp_5)
//  Fictorizes <src> as k*(5^exp)
//  Returns:
//  * factor k
//  * exp_5 - exponent of 5
{
	exp_5 = 0;
	if(src == 0)    return 0;

	DWORD rslt = src;

	while((mod_5(rslt) == 0) && (rslt != 1))
	{
		exp_5++;
		rslt = div_5(rslt);
	}

	return rslt;
}
//---------------------------------------------------------------------------
int mod_5(DWORD src)
//  Modulus of 5
//  Returns:
//  * remainder of division by 5
{
	int r_5 = 0;

	if(src != 0)
	{
		DWORD mask;
		__asm
		{
			//  Get the index of the not zero MS bit
			mov EAX, [src]
			bsr EAX, EAX

			//  Set <mask> to the not zero MS bit
			mov CL, AL
			mov EAX, 1
			shl EAX, CL
			mov [mask], EAX
		}

		while(mask != 0)
		{
		#if defined __F_35_BE2_MOD__
			const DWORD tt5 = 0x220CB310;   //  Transition Table
			__asm
			{
				//  Check if (src & mask) != 0
				mov EAX, [src]
				and EAX, [mask]
				xor EDX, EDX
				sub EDX, EAX
				sbb EAX, EAX
				and EAX, 1

				//  Triple index in tt
				//  inx = a + b
				//  a = r_5*3
				mov EDX, [r_5]
				shl EDX, 1
				add EDX, [r_5]
				//  b = 5*3*(src & mask)
				mov ECX, EAX
				shl ECX, 2
				add ECX, EAX
				mov EAX, ECX
				shl ECX, 1
                add ECX, EAX
				//  a + b
				add ECX, EDX

				//  Get triple at inx
				mov EAX, [tt5]
				shr EAX, CL
				and EAX, 0x00000007
				mov [r_5], EAX
			}
		#elif defined __F_35_BE_MOD__
			//  Transition Table
			static int tt5[2][5] = {{ 0, 2, 4, 1, 3}, { 1, 3, 0, 2, 4}};
			int inx = 0;
			__asm
			{
				mov EAX, [src]
				and EAX, [mask]
				//  Check if (src & mask) != 0
				xor EDX, EDX
				sub EDX, EAX
				sbb EAX, EAX
				and EAX, 1

				mov [inx], EAX
			}
			r_5 = tt5[inx][r_5];    //  Implemented with imul?!
		#else
			if(src & mask)
			{	//	Bit: 1
				//  Follow path 5
				if(r_5 == 1)    	r_5 = 3;
				else if(r_5 == 2)   r_5 = 0;
				else if(r_5 == 3)   r_5 = 2;
				else if(r_5 == 4)   r_5 = 4;
				else                r_5 = 1;
			}
			else
			{	// Bit: 0
				//  Follow path 5
				if(r_5 == 1)    	r_5 = 2;
				else if(r_5 == 2)   r_5 = 4;
				else if(r_5 == 3)   r_5 = 1;
				else if(r_5 == 4)   r_5 = 3;
			}
		#endif

			mask >>= 1;
		}
	}

	return r_5;
}
//---------------------------------------------------------------------------
DWORD div_5(DWORD divident)
//  https://stackoverflow.com/questions/17113660/divisiblity-of-5-without-using-and-operator
//  Henry S. Warren, Jr. Hacker's Delight
{
	__int64 q = static_cast<__int64>(divident) * 0x66666667;  // (2^33+3)/5
	return static_cast<DWORD>(q >> 33);
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

