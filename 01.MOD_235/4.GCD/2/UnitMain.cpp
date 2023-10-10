//---------------------------------------------------------------------------
//  Най-голям общ делител
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
#include <numeric>

#include "UnitMain.h"
//---------------------------------------------------------------------------
const DWORD BEG = 0;
const DWORD N 	= 32;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Great Common Divisor" << std::endl;
	std::cout << "[STD Implementation]" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << std::dec << std::setw(3) << std::setfill(' ');
		std::cout << " " << std::gcd(i, 2) << "|"  << std::gcd(i, 3) << "|" << std::gcd(i, 5) << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

