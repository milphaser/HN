//---------------------------------------------------------------------------
//  Fast Integer Division by 3
//---------------------------------------------------------------------------
//  https://stackoverflow.com/questions/11694546/divide-a-number-by-3-without-using-operators
//  Modification: Serial addition replaced with parallel
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>
//#include <stdio.h>

#include <iostream>
#include <iomanip>

#include "UnitMain.h"
//---------------------------------------------------------------------------
const int BEG 	= 0;
const int N		= 256;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Fast Integer Division by 3" << std::endl << std::endl;

	for(int i = BEG; i < BEG + N; i++)
	{
		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << " " << std::dec << std::setw(3) << std::setfill(' ') << i/3;
		std::cout << "|" << std::dec << std::setw(3) << std::setfill(' ') << div_3(i);
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << div_3(i) << "]";

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
UINT div_3(UINT dividend)
{
	UINT quotient = 0;

	while(dividend > 3)
	{
		quotient = quotient + (dividend >> 2);
		dividend = (dividend >> 2) + (dividend & 3);
	}

	if(dividend == 3)
	{
		quotient = quotient + 1;
	}

	return quotient;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

