//---------------------------------------------------------------------------
//  Бързо целочислено деление на 3
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
const DWORD BEG 	= 128;
const DWORD N 		= 32;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Fast Integer Division by 3" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << " " << std::dec << std::setw(3) << std::setfill(' ') << i/3;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << div_3(i) << "]";

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
DWORD div_3(DWORD divident)
//  https://stackoverflow.com/questions/11694546/divide-a-number-by-3-without-using-operators
{
	DWORD sum = 0;

	while(divident > 3)
	{
		sum = __add(divident >> 2, sum);
		divident = __add(divident >> 2, divident & 3);
	}

	if(divident == 3)
	{
		sum = __add(sum, 1);
	}

	return sum;
}
//---------------------------------------------------------------------------
DWORD __add(DWORD x, DWORD y)
{
	while (x)
	{
		DWORD t = (x & y) << 1;
		y = y ^ x;
		x = t;
	}

	return y;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

