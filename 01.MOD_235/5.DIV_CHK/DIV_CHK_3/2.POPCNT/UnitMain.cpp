//---------------------------------------------------------------------------
//  DIVISIBILITY CHECK BY 3
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
//#include <numeric>

#include "UnitMain.h"
//---------------------------------------------------------------------------
const DWORD BEG = 0;
const DWORD N 	= 31;
//const DWORD BEG = 0;
//const DWORD N 	= 0xFFFF;
//const DWORD BEG	= 0xFFFF;
//const DWORD N	= 0xFF;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Divisibility Check by 3" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << std::dec << std::setw(3) << std::setfill(' ');
		std::cout << " " << div_chk_3(i) << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
BOOL div_chk_3(DWORD src)
{
	BOOL rslt = false;

	//  Short Code Diversity Table
	const DWORD scdt = 0x00009249;
	// FEDC BA98 7654 3210
	// 1001 0010 0100 1001

	__asm
	{
        //  EAX - general buffer
		//	ECX	- cnt_odd, counter of odd bits
		//	EDX	- cnt_evn, counter of even bits

		mov EAX, [src]
		and EAX, 0x55555555 //  even bits: 0101 0101 0101 0101 0101 0101 0101 0101
		popcnt EDX, EAX

		mov EAX, [src]
		and EAX, 0xAAAAAAAA //  odd bits: 1010 1010 1010 1010 1010 1010 1010 1010
		popcnt ECX, EAX

		//  cnt_odd - cnt_evn
		sub ECX, EDX
		mov EAX, ECX

		//  abs(cnt_odd - cnt_evn)
		cdq
		xor EAX, EDX
		sub EAX, EDX

		mov ECX, EAX

		mov EAX, [scdt]
		shr EAX, CL
		and EAX, 0x1

		mov [rslt], EAX
	}

	return rslt;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

