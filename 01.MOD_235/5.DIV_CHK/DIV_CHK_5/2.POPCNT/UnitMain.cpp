//---------------------------------------------------------------------------
//  DIVISIBILITY CHECK BY 5
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
	std::cout << "Divisibility Check by 5" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << std::dec << std::setw(3) << std::setfill(' ');
		std::cout << " " << div_chk_5(i) << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
BOOL div_chk_5(DWORD src)
{
	BOOL rslt = false;

	//  Short Code Diversity Table
	const DWORD scdt = 0x00008421;
	// FEDC BA98 7654 3210
	// 1000 0100 0010 0001

	__asm
	{
		//  EAX - general buffer
		//	ECX	- cnt_odd, counter of odd bit pairs
		//	EDX	- cnt_evn, counter of even bit pairs

		mov EAX, [src]
		and EAX, 0x22222222 //  even pairs/hi bit: 0010 0010 0010 0010 0010 0010 0010 0010
		popcnt EDX, EAX
		shl EDX, 1
		mov EAX, [src]
		and EAX, 0x11111111 //  even pairs/lo bit: 0001 0001 0001 0001 0001 0001 0001 0001
		popcnt EAX, EAX
		add EDX, EAX

		mov EAX, [src]
		and EAX, 0x88888888 //  odd pairs/hi bit: 1000 1000 1000 1000 1000 1000 1000 1000
		popcnt ECX, EAX
		shl ECX, 1
		mov EAX, [src]
		and EAX, 0x44444444 //  odd pairs/lo bit: 0100 0100 0100 0100 0100 0100 0100 0100
		popcnt EAX, EAX
		add ECX, EAX

		sub ECX, EDX
		//  abs(cnt_odd - cnt_evn)
		mov EAX, ECX
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

