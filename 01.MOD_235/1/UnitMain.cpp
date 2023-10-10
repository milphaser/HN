//---------------------------------------------------------------------------
//  Проверка за делимост на 2, 3 и 5
//  С използване на "Детерминиран краен автомат" (DFA)
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
const DWORD N 	= 32;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Checking Divisibility by 2, 3 and 5" << std::endl << std::endl;
	std::cout << "ver. 1 MSB to LSB scan" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		int r_2_ = i % 2;
		int r_3_ = i % 3;
		int r_5_ = i % 5;

		int r_2 = mod_2(i);
		int r_3 = mod_3(i);
		int r_5 = mod_5(i);

		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << std::dec << std::setw(3) << std::setfill(' ');
		std::cout << " " << r_2_ << "/" << r_2;
		std::cout << " " << r_3_ << "/" << r_3;
		std::cout << " " << r_5_ << "/" << r_5;

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
int mod_2(DWORD src)
//  Modulus of 2
//  Returns:
//  * remainder of division by 2
{
	int r_2 = 0;
	DWORD mask = 0x80000000;
	const int len = sizeof(DWORD) * 8;

	//  MSB to LSB
	for(int i = 0; i < len; i++, mask >>= 1)
	{
		if(src & mask)
		{	//	Bit: 1
			//  Follow path 2
			r_2 = 1;
		}
		else
		{	// Bit: 0
			//  Follow path 2
			r_2 = 0;
		}
	}

	return r_2;
}
//---------------------------------------------------------------------------
int mod_3(DWORD src)
//  Modulus of 3
//  Returns:
//  * remainder of division by 3
{
	int r_3 = 0;
	DWORD mask = 0x80000000;
	const int len = sizeof(DWORD) * 8;

	//  MSB to LSB
	for(int i = 0; i < len; i++, mask >>= 1)
	{
		if(src & mask)
		{	//	Bit: 1
			//  Follow path 3
			if(r_3 == 1)    	r_3 = 0;
			else if(r_3 == 2)   r_3 = 2;
			else                r_3 = 1;
		}
		else
		{	// Bit: 0
			//  Follow path 3
			if(r_3 == 1)    	r_3 = 2;
			else if(r_3 == 2)   r_3 = 1;
		}
	}

	return r_3;
}
//---------------------------------------------------------------------------
int mod_5(DWORD src)
//  Modulus of 5
//  Returns:
//  * remainder of division by 5
{
	int r_5 = 0;
	DWORD mask = 0x80000000;
	const int len = sizeof(DWORD) * 8;

	//  MSB to LSB
	for(int i = 0; i < len; i++, mask >>= 1)
	{
		if(src & mask)
		{	//	Bit: 1
			//  Follow path 5
			if(r_5 == 1)    	r_5 = 3;
			else if(r_5 == 2)   r_5 = 0;
			else if(r_5 == 3)   r_5 = 2;
			else if(r_5 == 4)   r_5 = 4;
			else                r_5 = 1;
		}
		else
		{	// Bit: 0
			//  Follow path 5
			if(r_5 == 1)    	r_5 = 2;
			else if(r_5 == 2)   r_5 = 4;
			else if(r_5 == 3)   r_5 = 1;
			else if(r_5 == 4)   r_5 = 3;
		}
	}

	return r_5;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

