//---------------------------------------------------------------------------
//  Fast Integer Division by 3 and 5
//---------------------------------------------------------------------------
//  Source: Henry S. Warren, Jr. Hacker's Delight
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
	std::cout << "Fast Integer Division by 3 and 5" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << " " << std::dec << std::setw(3) << std::setfill(' ') << i/3;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << div_3(i) << "]";
		std::cout << " " << std::dec << std::setw(3) << std::setfill(' ') << i/5;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << div_5(i) << "]";

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
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
DWORD div_5(DWORD divident)
//  https://stackoverflow.com/questions/17113660/divisiblity-of-5-without-using-and-operator
//  Henry S. Warren, Jr. Hacker's Delight
{
	__int64 q = static_cast<__int64>(divident) * 0x66666667;  // (2^33+3)/5
	return static_cast<DWORD>(q >> 33);
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

