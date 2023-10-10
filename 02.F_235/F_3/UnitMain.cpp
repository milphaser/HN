//---------------------------------------------------------------------------
//  Факторизация от вида к*(3^exp)
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
	std::cout << "Factorization as k*(3^exp)" << std::endl;
	#if defined __F_35_BE_MOD__
		std::cout << "[Branch Elimination Technique]" << std::endl;
	#elif defined __F_35_BE2_MOD__
		std::cout << "[Branch Elimination Technique 2]" << std::endl;
	#endif
	std::cout << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		int exp_3;
		DWORD k = f_3(i, exp_3);

		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << " " << std::dec << std::setw(3) << std::setfill(' ')
				  << k << "*(3^" << exp_3 << ")";

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
DWORD f_3(DWORD src, int& exp_3)
//  Fictorizes <src> as k*(3^exp)
//  Returns:
//  * factor k
//  * exp_3 - exponent of 3
{
	exp_3 = 0;
	if(src == 0)    return 0;

	DWORD rslt = src;

	while((mod_3(rslt) == 0) && (rslt != 1))
	{
		exp_3++;
		rslt = div_3(rslt);
    }

	return rslt;
}
//---------------------------------------------------------------------------
int mod_3(DWORD src)
//  Modulus of 3
//  Returns:
//  * remainder of division by 3
{
	int r_3 = 0;

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
			const DWORD tt3 = 0x00000858;   //  Transition Table
			__asm
			{
				//  Check if (src & mask) != 0
				mov EAX, [src]
				and EAX, [mask]
				xor EDX, EDX
				sub EDX, EAX
				sbb EAX, EAX
				and EAX, 1

				//  Pair index in tt
				//  inx = a + b
				//  a = r_3*2
				mov EDX, [r_3]
				shl EDX, 1
				//  b = 3*2*(src & mask)
				mov ECX, EAX
				shl ECX, 1
				add ECX, EAX
				shl ECX, 1
				//  a + b
				add ECX, EDX

				//  Get pair at inx
				mov EAX, [tt3]
				shr EAX, CL
				and EAX, 0x00000003
				mov [r_3], EAX
			}
		#elif defined __F_35_BE_MOD__
			//  Transition Table
			static int tt3[2][3] = {{0, 2, 1}, {1, 0, 2}};
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
			r_3 = tt3[inx][r_3];    //  Implemented with imul?!
		#else
			if(src & mask)
			{	//	Bit: 1
				//  Follow path 3
				if(r_3 == 1)    	r_3 = 0;
				else if(r_3 == 2)   r_3 = 2;
				else                r_3 = 1;
			}
			else
			{	// Bit: 0
				//  Follow path 3
				if(r_3 == 1)    	r_3 = 2;
				else if(r_3 == 2)   r_3 = 1;
			}
		#endif

			mask >>= 1;
		}
	}

	return r_3;
}
//---------------------------------------------------------------------------
DWORD div_3(DWORD divident)
//  https://stackoverflow.com/questions/20450643/division-by-3-without-division-operator?rq=3
//  Henry S. Warren, Jr. Hacker's Delight
{
	__int64 q = static_cast<__int64>(divident) * 0xAAAAAAAB;  // (2^33+1)/3
	return static_cast<DWORD>(q >> 33);
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

