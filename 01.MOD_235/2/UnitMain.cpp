//---------------------------------------------------------------------------
//  Проверка за делимост на 2, 3 и 5
//  С използване на "Детерминиран краен автомат" (DFA)
//  Съкращаване броя на циклите, започвайки от най-старшия ненулев бит
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
const DWORD N 	= 15;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Checking Divisibility by 2, 3 and 5" << std::endl;
	std::cout << "ver. 2 Reduction of loops: start for the non zero MS bit" << std::endl;
	#if defined __F_35_BE_MOD__
		std::cout << "       [Branch Elimination Technique]" << std::endl;
	#elif defined __F_35_BE2_MOD__
		std::cout << "       [Branch Elimination Technique 2]" << std::endl;
	#endif
	std::cout << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		int r_2_ = i % 2;
		int r_3_ = i % 3;
		int r_5_ = i % 5;

		int r_2 = mod_2(i);
		int r_3 = mod_3(i);
		int r_5 = mod_5(i);

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
int mod_2(DWORD src)
//  Modulus of 2
//  Returns:
//  * remainder of division by 2
{
	return src & 1;
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
//#pragma package(smart_init)

