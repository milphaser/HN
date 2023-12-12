//---------------------------------------------------------------------------
//	Multi-word Namespace Arithmetic Test
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused

#include <iostream>
#include <iomanip>

#include <fstream>
#include <chrono>
#include <numeric>

#include "UnitMain.h"
#include "UnitMW.h"
//---------------------------------------------------------------------------
const int MW_SIZE = 4;      // Multi-word Size in Double Words
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Multi-word Namespace ver." << MW::ver << std::endl;
	std::cout << "Arithmetic Test" << std::endl;

	MW::INT_T<MW_SIZE> S;           // Sum
	MW::INT_T<MW_SIZE> D;           // Difference
	MW::INT_T<MW_SIZE> P;           // Product
	MW::INT_T<MW_SIZE>::DIV_T Q;    // Quotient & Reminder

	// MW_SIZE * 32 bits
	std::array<UINT, MW_SIZE> arr = {0x40000000, 0x40000000, 0x40000000, 0x40000000};
	MW::INT_T<MW_SIZE> X(arr);      // Operand

	std::cout << std::endl;
	system("pause");
	system("cls");

	////  Second Term: 2 ////////////////////////////////////////////////////
	//
	std::cout << "X" << " [" << std::to_string(X.digits()) << " bits]" << std::endl;
	std::cout << X << std::endl;
	//
	std::cout << "S = X + X" << std::endl;
	S = X; S += X;
	std::cout << S << std::endl;
	//
	std::cout << "D = S - X" << std::endl;
	D = S; D -= X;
	std::cout << D << std::endl;
	//
	std::cout << "P = X x 2" << std::endl;
	P = X.mul(2);
	std::cout << P << std::endl;
	//
	std::cout << "P = X x 2 (mul_2)" << std::endl;
	P = X.mul_2();
	std::cout << P << std::endl;
	//
	std::cout << "Q = P / 2" << std::endl;
	Q = P.div(2);
	std::cout << Q.quot << " | " << Q.rem << std::endl;
	//
	std::cout << "P = Q x 2" << std::endl;
	P = Q.quot.mul_2();
	std::cout << P << std::endl;
	//
	std::cout << "P = Q x 2 + R (Recovered X x 2)" << std::endl;
	P += Q.rem;
	std::cout << P << std::endl;
	/////////////////////////////////////////////////////////////////////////

	std::cout << std::endl;
	system("pause");
	system("cls");

	////  Second Term: 3 ////////////////////////////////////////////////////
	//
	std::cout << "X" << " [" << std::to_string(X.digits()) << " bits]" << std::endl;
	std::cout << X << std::endl;
	//
	std::cout << "S = X + X + X" << std::endl;
	S = X; S += X; S += X;
	std::cout << S << std::endl;
	//
	std::cout << "D = S - X - X" << std::endl;
	D = S; D -= X; D -= X;
	std::cout << D << std::endl;
	//
	std::cout << "P = X x 3" << std::endl;
	P = X.mul(3);
	std::cout << P << std::endl;
	//
	std::cout << "P = X x 3 (mul_3)" << std::endl;
	P = X.mul_3();
	std::cout << P << std::endl;
	//
	std::cout << "Q = P / 3" << std::endl;
	Q = P.div(3);
	std::cout << Q.quot << " | " << Q.rem << std::endl;
	//
	std::cout << "P = Q x 3" << std::endl;
	P = Q.quot.mul_3();
	std::cout << P << std::endl;
	//
	std::cout << "P = Q x 3 + R (Recovered X x 3)" << std::endl;
	P += Q.rem;
	std::cout << P << std::endl;
	/////////////////////////////////////////////////////////////////////////

	std::cout << std::endl;
	system("pause");
	system("cls");

	////  Second Term: 5 ////////////////////////////////////////////////////
	//
	std::cout << "X" << " [" << std::to_string(X.digits()) << " bits]" << std::endl;
	std::cout << X << std::endl;
	//
	std::cout << "S = X + X + X + X + X" << std::endl;
	S = X; S += X; S += X; S += X; S += X;
	std::cout << S << std::endl;
	//
	std::cout << "D = S - X - X - X - X" << std::endl;
	D = S; D -= X; D -= X; D -= X; D -= X;
	std::cout << D << std::endl;
	//
	std::cout << "P = X x 5" << std::endl;
	P = X.mul(5);
	std::cout << P << std::endl;
	//
	std::cout << "P = X x 5 (mul_5)" << std::endl;
	P = X.mul_5();
	std::cout << P << std::endl;
	//
	std::cout << "Q = P / 5" << std::endl;
	Q = P.div(5);
	std::cout << Q.quot << " | " << Q.rem << std::endl;
	//
	std::cout << "P = Q x 5" << std::endl;
	P = Q.quot.mul_5();
	std::cout << P << std::endl;
	//
	std::cout << "P = Q x 5 + R (Recovered X x 5)" << std::endl;
	P += Q.rem;
	std::cout << P << std::endl;
	/////////////////////////////////////////////////////////////////////////

	std::cout << std::endl;
	system("pause");
	system("cls");

	////  MW Binary to Decimal Conversion ///////////////////////////////////
	//
	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::stringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), "..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");

	std::ofstream of(fn.str());		// Output log file
	std::stringstream ss;

	ss << "MW Namespace ver." << MW::ver << std::endl;
	ss << "MW Binary to Decimal Conversion\n\n";
	std::cout << "Please, wait..." << std::endl << std::endl;

	if(of)
	{
		auto beg = std::chrono::steady_clock::now();

		X = {0x0, 0x0, 0x0, 0xFFFFFFFF};
		ss << "[" << std::to_string(X.digits()) << " bits]\n";
		ss << "BIN: " << X << std::endl;
		ss << "DEC: "<< X.to_dec_string() << "\n\n";

		X = {0x0, 0x0, 0xFFFFFFFF, 0xFFFFFFFF};
		ss << "[" << std::to_string(X.digits()) << " bits]\n";
		ss << "BIN: " << X << std::endl;
		ss << "DEC: "<< X.to_dec_string() << "\n\n";

		X = {0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		ss << "[" << std::to_string(X.digits()) << " bits]\n";
		ss << "BIN: " << X << std::endl;
		ss << "DEC: "<< X.to_dec_string() << "\n\n";

		X = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		ss << "[" << std::to_string(X.digits()) << " bits]\n";
		ss << "BIN: " << X << std::endl;
		ss << "DEC: "<< X.to_dec_string() << "\n\n";

		MW::INT_T<2*MW_SIZE> X2;
		X2 = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        X2 -= 1;
		ss << "[" << std::to_string(X2.digits()) << " bits]\n";
		ss << "BIN: " << X2 << std::endl;
		ss << "DEC: "<< X2.to_dec_string() << "\n\n";

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

		ss << "T: " << duration.count() << ", microseconds" << std::endl;

		ss << std::endl;

		std::cout << ss.str();
		of << ss.str();
	}

	if(of.good())
	{
		std::cout << "Log saved to <" << fn.str() << "> file" << std::endl << std::endl;
	}
	else
	{
		std::cout << "Log file <" << fn.str() << "> error" << std::endl << std::endl;
	}
	of.close();

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

