//---------------------------------------------------------------------------
//	Integer Division
//  With Successive Subtraction of the Divisor
//	VERY INEFFICIENT
//	ONLY FOR ILLUSTRATION
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused

#include <tchar.h>
//#include <stdio.h>

#include <iostream>
#include <iomanip>
#include <limits>

#include "UnitMain.h"
//---------------------------------------------------------------------------
const DWORD BEG = 0;
const DWORD N 	= 16;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Integer Division" << std::endl;
	std::cout << "With Successive Subtraction of the Divisor" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		auto dt_3 = std::div(i, 3);
		auto dt_5 = std::div(i, 5);

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
std::div_t div(const DWORD dividend, const DWORD divisor)
//  https://www.geeksforgeeks.org/divide-two-integers-without-using-multiplication-division-mod-operator/
//  Division With Successive Subtraction of the Divisor
//	VERY INEFFICIENT
//	ONLY FOR ILLUSTRATION
{
	std::div_t result;

	if(divisor == 0)
	{
		//  OVERFLOW
		result.quot = std::numeric_limits<DWORD>::max();
		result.rem = 0;
	}
	else
	{
		result.quot = 0;
		result.rem  = dividend;

		while(result.rem >= divisor)
		{
			result.rem -= divisor;
			result.quot++;
		}
	}

	return result;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

