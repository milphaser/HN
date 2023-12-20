//---------------------------------------------------------------------------
//  Multi-word Decimal to Internal (Binary) Conversion
//---------------------------------------------------------------------------
//	Multi-word HN Namespace ver.0.85
//	Multi-word Namespace ver.0.15 to ver.0.17 Evolution
//
//  Status: Under Development
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
	std::cout << "Multi-word Namespace ver." << MW::ver << std::endl;
	std::cout << "Multi-word Decimal to Internal (Binary) Conversion" << std::endl;

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
				{0xC00000F0, 0xC00000F0, 0xC00000F0, 0xC00000F0};
			MW::INT_T<MW_SIZE> X;
			X = arr;
			ss << "    X: " << X << "\n";
			X <<= 1;
			ss << "SHL 1: " << X << "\n";
			X <<= 4;
			ss << "SHL 4: " << X << "\n\n";
		}

		{
			std::array<UINT, MW_SIZE> arr =
				{0x0F000003, 0x0F000003, 0x0F000003, 0x0F000003};
			MW::INT_T<MW_SIZE> X;
			X = arr;
			ss << "    X: " << X << "\n";
			X >>= 1;
			ss << "SHR 1: " << X << "\n";
			X >>= 4;
			ss << "SHR 4: " << X << "\n\n";
		}

		{
			std::string str = "0x12345678:9ABCDEF0:12345678:9ABCDEF0";
			MW::INT_T<MW_SIZE> X;
            X = str;
			ss << "    X: " << X << "\n\n";
		}

		{
			std::string str = "0x12345678";
			MW::INT_T<MW_SIZE> X;
			X = str;
			ss << "    X: " << X << "\n";
			MW::INT_T<MW_SIZE> P;
			P = X.mul_10();
			ss << " X*10: " << P << "\n\n";
		}

		{
			std::string str = "4 294 967 295";
			MW::INT_T<MW_SIZE> X;
			X = str;
			ss << "    X: " << X << "\n\n";
		}

		{
			std::string str = "4 294 967 296";
			MW::INT_T<MW_SIZE> X;
			X = str;
			ss << "    X: " << X << "\n\n";
		}

		{
			std::string str = "4 294 967 297";
			MW::INT_T<MW_SIZE> X;
			X = str;
			ss << "    X: " << X << "\n\n";
		}

		{
			std::string str = "340 282 366 920 938 463 463 374 607 431 768 211 455";
			MW::INT_T<MW_SIZE> X;
			X = str;
			ss << "    X: " << X << "\n\n";
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

