//---------------------------------------------------------------------------
//  Fast Integer Division by 3
//---------------------------------------------------------------------------
//  https://stackoverflow.com/questions/11694546/divide-a-number-by-3-without-using-operators
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
	UINT sum = 0;

	while(dividend > 3)
	{
		sum = srl_add(dividend >> 2, sum);
		dividend = srl_add(dividend >> 2, dividend & 3);
	}

	if(dividend == 3)
	{
		sum = srl_add(sum, 1);
	}

	return sum;
}
//---------------------------------------------------------------------------
UINT srl_add(UINT x, UINT y)
//  Serial Addition
//  NOTE: Use parallel addition instead
{
	while (x)
	{
		UINT t = (x & y) << 1;
		y = y ^ x;
		x = t;
	}

	return y;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

