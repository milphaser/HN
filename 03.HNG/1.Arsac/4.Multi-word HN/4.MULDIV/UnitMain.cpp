//---------------------------------------------------------------------------
//  Multi-word Total Multiplication/Division Test
//---------------------------------------------------------------------------
//	Multi-word HN Namespace ver.0.85
//	Multi-word Namespace ver.0.19
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

//#include <chrono>
//#include <numeric>
//---------------------------------------------------------------------------
#include "UnitHN.h"
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
	std::cout << "Multi-word Namespace ver." << MW::ver << "\n";
	std::cout << "Multi-word Total Multiplication/Division Test\n";

	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::stringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), "..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");

	std::ofstream of(fn.str());		// Output log file
	std::stringstream ss;

	ss << "MW Namespace ver." << MW::ver << "\n";
	ss << "MW Total Multiplication/Division Test\n\n";
	std::cout << "Please, wait...\n\n";

	if(of)
	{
		auto beg = std::chrono::steady_clock::now();

		{
			std::array<UINT, MW_SIZE> arr =
				{0x0, 0x0, 0x0, 0x0};
			MW::INT_T<MW_SIZE> X;
			X = arr;
			X -= 1;
			ss << "  Max  [" << std::to_string(X.digits()) << " bits]\n";
			ss << "  BIN: " << X << "\n";
			ss << "  DEC: " << X.to_dec_string() << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE> arr =
				{0x01234567, 0x89abcdef, 0x01234567, 0x89abcdef};
			MW::INT_T<MW_SIZE> X(arr);
			MW::INT_T<2*MW_SIZE> X2;
			X2 = MW::extend(X);
			ss << "    X: " << X << "\n";
			ss << "EXT X: " << X2 << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE> arr =
				{0x33333333, 0x55555555, 0x77777777, 0xAAAAAAAA};
			MW::INT_T<MW_SIZE> X(arr);
			MW::INT_T<MW_SIZE/2> HI, LO;
			HI = MW::split_hi<MW_SIZE/2>(X);
			LO = MW::split_lo<MW_SIZE/2>(X);
			ss << "    X: " << X << "\n";
			ss << " HI X: " << HI << "\n";
			ss << " LO X: " << LO << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE/2> multiplicand =
				{0xFFFFFFFF, 0xFFFFFFFF};
			std::array<UINT, MW_SIZE/2> multiplier =
				{0x0, 0x00000001};
			MW::INT_T<MW_SIZE/2> X(multiplicand);
			MW::INT_T<MW_SIZE/2> Y(multiplier);
			MW::INT_T<MW_SIZE> Z = mul(X, Y);
			ss << "    X: " << X << "\n";
			ss << "    Y: " << Y << "\n";
			ss << "  X*Y: " << Z << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE/2> multiplicand =
				{0xFFFFFFFF, 0xFFFFFFFF};
			std::array<UINT, MW_SIZE/2> multiplier =
				{0x00000001, 0x0};
			MW::INT_T<MW_SIZE/2> X(multiplicand);
			MW::INT_T<MW_SIZE/2> Y(multiplier);
			MW::INT_T<MW_SIZE> Z = mul(X, Y);
			ss << "    X: " << X << "\n";
			ss << "    Y: " << Y << "\n";
			ss << "  X*Y: " << Z << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE/2> multiplicand =
				{0xFFFFFFFF, 0xFFFFFFFF};
			std::array<UINT, MW_SIZE/2> multiplier =
				{0xFFFFFFFF, 0xFFFFFFFF};
			MW::INT_T<MW_SIZE/2> X(multiplicand);
			MW::INT_T<MW_SIZE/2> Y(multiplier);
			MW::INT_T<MW_SIZE> Z = mul(X, Y);
			ss << "    X: " << X << "\n";
			ss << "    Y: " << Y << "\n";
			ss << "  X*Y: " << Z << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE/2> multiplicand =
				{0x0, 0xFFFFFFFF};
			std::array<UINT, MW_SIZE/2> multiplier =
				{0x0, 0xFFFFFFFF};
			MW::INT_T<MW_SIZE/2> X(multiplicand);
			MW::INT_T<MW_SIZE/2> Y(multiplier);
			MW::INT_T<MW_SIZE> Z = mul(X, Y);
			ss << "    X: " << X << "\n";
			ss << "    Y: " << Y << "\n";
			ss << "  X*Y: " << Z << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE> dividend =
				{0x0, 0x0, 0x0, 0x000FFFFF};
			std::array<UINT, MW_SIZE> divisor =
				{0x0, 0x0, 0x0, 0x00000001};
			MW::INT_T<MW_SIZE> X(dividend);
			MW::INT_T<MW_SIZE> Y(divisor);
			MW::DIV_T<MW_SIZE> Z = div(X, Y);
			ss << "    X: " << X << "\n";
			ss << "    Y: " << Y << "\n";
			ss << " Quot: " << Z.quot << "\n";
			ss << "  Rem: " << Z.rem << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE> dividend =
				{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
			std::array<UINT, MW_SIZE> divisor =
				{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
			MW::INT_T<MW_SIZE> X(dividend);
			MW::INT_T<MW_SIZE> Y(divisor);
			MW::DIV_T<MW_SIZE> Z = div(X, Y);
			ss << "    X: " << X << "\n";
			ss << "    Y: " << Y << "\n";
			ss << " Quot: " << Z.quot << "\n";
			ss << "  Rem: " << Z.rem << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE> dividend =
				{0x0, 0x1, 0xFFFFFFFF, 0xFFFFFFFF};
			std::array<UINT, MW_SIZE> divisor =
				{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
			MW::INT_T<MW_SIZE> X(dividend);
			MW::INT_T<MW_SIZE> Y(divisor);
			MW::DIV_T<MW_SIZE> Z = div(X, Y);
			ss << "    X: " << X << "\n";
			ss << "    Y: " << Y << "\n";
			ss << " Quot: " << Z.quot << "\n";
			ss << "  Rem: " << Z.rem << "\n\n";
		}

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
//#pragma package(smart_init)

