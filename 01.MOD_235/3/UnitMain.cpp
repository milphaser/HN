//---------------------------------------------------------------------------
//  Проверка за делимост на 2, 3 и 5
//  С използване на "Детерминиран краен автомат" (DFA)
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
const DWORD BEG = 0;
const DWORD N 	= 32;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Checking Divisibility by 2, 3 and 5" << std::endl;
	#if defined __F_35_BE_MOD__
	std::cout << "[Branch Elimination Technique]" << std::endl;
	#endif
	std::cout << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		int r_2_ = i % 2;
		int r_3_ = i % 3;
		int r_5_ = i % 5;

		int r_2, r_3, r_5;
		mod_235(i, r_2, r_3, r_5);

		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << std::dec << std::setw(3) << std::setfill(' ');
		std::cout << " " << r_2_ << "/" << r_2;
		std::cout << " " << r_3_ << "/" << r_3;
		std::cout << " " << r_5_ << "/" << r_5;

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
void mod_235(DWORD src, int& r_2, int& r_3, int& r_5)
//  Modulus of 2, 3 and 5.
//  Returns:
//  * r_2 - remainder of division by 2
//  * r_3 - remainder of division by 3
//  * r_5 - remainder of division by 5
{
	r_2 = r_3 = r_5 = 0;

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
		#if defined __F_35_BE_MOD__
			//  Transition Table
			static int tt3[2][3] = {{0, 2, 1}, {1, 0, 2}};
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
			r_2 = inx;
			r_3 = tt3[inx][r_3];
			r_5 = tt5[inx][r_5];
		#else
			if(src & mask)
			{	//	Bit: 1
				//  Follow path 2
				r_2 = 1;

				//  Follow path 3
				if(r_3 == 1)    	r_3 = 0;
				else if(r_3 == 2)   r_3 = 2;
				else                r_3 = 1;

				//  Follow path 5
				if(r_5 == 1)    	r_5 = 3;
				else if(r_5 == 2)   r_5 = 0;
				else if(r_5 == 3)   r_5 = 2;
				else if(r_5 == 4)   r_5 = 4;
				else                r_5 = 1;
			}
			else
			{	// Bit: 0
				//  Follow path 2
				r_2 = 0;

				//  Follow path 3
				if(r_3 == 1)    	r_3 = 2;
				else if(r_3 == 2)   r_3 = 1;

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
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

