//---------------------------------------------------------------------------
//  Целочислено деление
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
const DWORD N 	= 16;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Integer Division" << std::endl;
	std::cout << "(std::div implementation)" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		std::div_t dt_3, dt_5;
		dt_3 = std::div(i, 3);
		dt_5 = std::div(i, 5);

		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << std::dec << std::setw(3) << std::setfill(' ');
		std::cout << " " << dt_3.quot << "|" << dt_3.rem;
		std::cout << " " << dt_5.quot << "|" << dt_5.rem;

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

