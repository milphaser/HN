//---------------------------------------------------------------------------
//  Факторизация от вида к*(2^exp)
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
	std::cout << "Factorization as k*(2^exp)" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		int exp_2;
		DWORD k = f_2(i, exp_2);

		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << " " << std::dec << std::setw(3) << std::setfill(' ')
				  << k << "*(2^" << exp_2 << ")";

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
DWORD f_2(DWORD src, int& exp_2)
//  Fictorizes <src> as k*(2^exp)
//  Returns:
//  * factor k
//  * exp_2 - exponent of 2
{
	exp_2 = 0;
	if(src == 0)    return 0;

	for(; src != 0; src >>= 1)
	{
		if(src & 1) break;
		exp_2++;
	}

	return src;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

