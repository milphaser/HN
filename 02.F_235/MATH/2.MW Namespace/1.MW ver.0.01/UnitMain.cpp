//---------------------------------------------------------------------------
//	Multi-word Multiplication by 2
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused

#include <iostream>
#include <iomanip>

#include "UnitMain.h"
#include "UnitMW.h"
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Multiplication of 64 bit multiplicand by 32 bit multiplier" << std::endl;
	std::cout << "[Multi-word Namespace ver." << MW::ver << "]" << std::endl << std::endl;

	MW::INT_T<4> tmp;   // 128 бит///////////////
	tmp.arr = {0x40000000, 0x40000000, 0x40000000, 0x40000000};
	std::cout << "#"<< tmp.digits() << " bits" << std::endl;
	std::cout << tmp << std::endl;
	std::cout << tmp.mul_2() << std::endl;

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

