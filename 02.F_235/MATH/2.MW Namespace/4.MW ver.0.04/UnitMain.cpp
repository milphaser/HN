//---------------------------------------------------------------------------
//	Multi-word Division
//	(Multi-word Dividend/Double Word Divisor)
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
	std::cout << "Multi-word Multiplication by 2, 3 and 5" << std::endl;
	std::cout << "Multi-word Division (Multi-word Dividend/Double Word Divisor)" << std::endl;
	std::cout << "[Multi-word Namespace ver." << MW::ver << "]" << std::endl << std::endl;

	// 128 bit
	std::array<UINT, 4> arr = {0x40000000, 0x40000000, 0x40000000, 0x40000000};
	MW::INT_T<4> X(arr);
	MW::INT_T<4> P;
	MW::INT_T<4>::DIV_T Q;
	std::cout << "            #"<< X.digits() << " bits" << std::endl;

	P = X.mul_2();
	Q = P.div(2);
	std::cout << "        x = " << X << std::endl;
	std::cout << "P = X x 2 = " << P << std::endl;
	std::cout << "Q = P / 2 = " << Q.quot << " R = " << Q.rem << std::endl;
	P = Q.quot.mul_2();
	std::cout << "P = Q x 2 = " << P << std::endl;

	std::cout << std::endl;

	P = X.mul_3();
	Q = P.div(3);
	std::cout << "        x = " << X << std::endl;
	std::cout << "P = X x 3 = " << P << std::endl;
	std::cout << "Q = P / 3 = " << Q.quot << " R = " << Q.rem << std::endl;
	P = Q.quot.mul_3();
	std::cout << "P = Q x 3 = " << P << std::endl;

	std::cout << std::endl;

	P = X.mul_5();
	Q = P.div(5);
	std::cout << "        x = " << X << std::endl;
	std::cout << "P = X x 5 = " << P << std::endl;
	std::cout << "Q = P / 5 = " << Q.quot << " R = " << Q.rem << std::endl;
	P = Q.quot.mul_5();
	std::cout << "P = Q x 5 = " << P << std::endl;

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

