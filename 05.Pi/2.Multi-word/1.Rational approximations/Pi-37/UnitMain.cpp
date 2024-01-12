//---------------------------------------------------------------------------
//  Pi Calculation
//  Rational approximations
//
//  Source: Arndt, J., Ch. Haenel. Pi - Unleashed.
//	Springer-Verlag: Berlin, Heidelberg 2001
//  pi(37) =  2646693125139304345/842468587426513207
//---------------------------------------------------------------------------
//	Multi-word Namespace ver.0.21
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <tchar.h>
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
//---------------------------------------------------------------------------
#include "UnitMW.h"
#include "UnitMain.h"
//---------------------------------------------------------------------------
//const int MW_SIZE = 1;	// Multi-word Size in Double Words [ 32 bits]
//const int MW_SIZE = 2;	// Multi-word Size in Double Words [ 64 bits]
//const int MW_SIZE = 3;	// Multi-word Size in Double Words [ 96 bits]
const int MW_SIZE = 4;	// Multi-word Size in Double Words [128 bits]
//const int MW_SIZE = 5;	// Multi-word Size in Double Words [160 bits]
//const int MW_SIZE = 6;	// Multi-word Size in Double Words [192 bits]
//const int MW_SIZE = 7;	// Multi-word Size in Double Words [224 bits]
//const int MW_SIZE = 8;	// Multi-word Size in Double Words [256 bits]
//const int MW_SIZE = 16;	// Multi-word Size in Double Words [512 bits]
//const int MW_SIZE = 32;	// Multi-word Size in Double Words [1024 bits]
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::stringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), "..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");

	std::ofstream of(fn.str());		// Output log file
	std::stringstream ss;

	ss << "MW Namespace ver." << MW::ver << "\n";
	ss << "Pi Calculation [Rational approximations]\n\n";

	std::cout << ss.str();
	ss.str("");

	std::cout << "Please, wait...\n\n";

	if(of)
	{
		MW::INT_T<MW_SIZE> X("2646693125139304345");
		MW::INT_T<MW_SIZE> Y("842468587426513207");

		ss << "Bits #" << Y.digits << " | ";
		ss << "Decimal Digits #" << Y.digits_dec << "\n\n";

		auto beg = std::chrono::steady_clock::now();

		ss << "     X: " << X.to_dec_string() << "\n";
		ss << "     Y: " << Y.to_dec_string() << "\n";

		std::pair<MW::INT_T<MW_SIZE>, MW::INT_T<MW_SIZE>> pi = MW::div_fp(X, Y);
		ss << "Pi(37): " << to_dec_string(pi) << "\n";

		ss << std::endl;

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

		ss << "T: " << std::dec << duration.count() << ", us" << std::endl;

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

	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
