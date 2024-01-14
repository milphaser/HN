//---------------------------------------------------------------------------
//  Pi Calculation
//  Machin Formula Multi-word Implementation
//---------------------------------------------------------------------------
//  Multi-word Namespace ver. 0.25
//---------------------------------------------------------------------------
//	arctan(1/5) = 1/5 - (1/5)^3/3 + (1/5)^5/5 - (1/5)^7/7 + ...
//	arctan(1/239) = 1/239 - (1/239)^3/3 + (1/239)^5/5 - (1/239)^7/7 + ...
//	pi/4 = 4 arctan(1/5) - arctan(1/239)
//
//	https://r-knott.surrey.ac.uk/Fibonacci/fibpi.html#section1.3
//  Arndt, J., Ch. Haenel. Pi - Unleashed. Springer-Verlag: Berlin, Heidelberg 2001
//---------------------------------------------------------------------------
//	Multi-word Namespace ver.0.22
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
#include "UnitMain.h"
//---------------------------------------------------------------------------
//const int MW_SIZE = 1;		// Multi-word Size in Double Words [      32 bits]
//const int MW_SIZE = 2;		// Multi-word Size in Double Words [      64 bits]
//const int MW_SIZE = 4;		// Multi-word Size in Double Words [     128 bits]
//const int MW_SIZE = 8;		// Multi-word Size in Double Words [     256 bits]
//const int MW_SIZE = 16;		// Multi-word Size in Double Words [     512 bits]
//const int MW_SIZE = 32;		// Multi-word Size in Double Words [    1024 bits]
//const int MW_SIZE = 64;		// Multi-word Size in Double Words [    2048 bits]
//const int MW_SIZE = 128;		// Multi-word Size in Double Words [    4096 bits]
//const int MW_SIZE = 256;		// Multi-word Size in Double Words [    8192 bits]
//const int MW_SIZE = 512;		// Multi-word Size in Double Words [   16384 bits]
//const int MW_SIZE = 1024;		// Multi-word Size in Double Words [   32768 bits]
//const int MW_SIZE = 2048;		// Multi-word Size in Double Words [   65536 bits]
//const int MW_SIZE = 4096;		// Multi-word Size in Double Words [  131072 bits]
//const int MW_SIZE = 8192;		// Multi-word Size in Double Words [  262144 bits]
//const int MW_SIZE = 16384;	// Multi-word Size in Double Words [  524288 bits]
//const int MW_SIZE = 32768;	// Multi-word Size in Double Words [ 1048576 bits]
//const int MW_SIZE = 65536;	// Multi-word Size in Double Words [ 2097152 bits]
const int MW_SIZE = 131072;	// Multi-word Size in Double Words [ 4194304 bits] <<<
//const int MW_SIZE = 262144;	// Multi-word Size in Double Words [ 8388608 bits]
//const int MW_SIZE = 524288;	// Multi-word Size in Double Words [16777216 bits]
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
	ss << "Pi Calculation [Machin Formula]\n\n";
	std::cout << ss.str();

	std::cout << "Please, wait...\n\n";

	if(of)
	{
		auto beg = std::chrono::steady_clock::now();

		MW::UINT iter_1_5 = 0, iter_1_239 = 0;

		auto arctan_1_5   = gregory_arctan<MW_SIZE>(5, iter_1_5);
		auto arctan_1_239 = gregory_arctan<MW_SIZE>(239, iter_1_239);

		//	pi/4 = 4 arctan(1/5) - arctan(1/239)
		auto pi_qurter_approximation_ext = arctan_1_5;
		pi_qurter_approximation_ext <<= 2;
		pi_qurter_approximation_ext -= arctan_1_239;

		//  Round Off
		MW::INT_T<2*MW_SIZE> r("0x80000000");
		if(MW_SIZE > 1)
			r <<= (MW_SIZE - 1);

		pi_qurter_approximation_ext += r;

		auto pi_qurter_approximation = MW::split_hi<MW_SIZE>(pi_qurter_approximation_ext);
		auto digits = pi_qurter_approximation.digits;
		auto digits_dec = pi_qurter_approximation.digits_dec;

		auto end = std::chrono::steady_clock::now();

		auto dur_us  = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

		std::pair<MW::INT_T<MW_SIZE>, MW::INT_T<MW_SIZE>> tmp;
		tmp.first = 0;

		tmp.second = pi_qurter_approximation;
		ss << "Pi/4 = " << to_dec_string(tmp) << "\n\n";

//		tmp.second = MW::split_hi<MW_SIZE>(arctan_1_5);
//		ss << "arctan(1/5)      = " << to_dec_string(tmp) << "\n";
		ss << "Iterations 1/5   #" << iter_1_5 << "\n";

//		tmp.second = MW::split_hi<MW_SIZE>(arctan_1_239);
//		ss << "arctan(1/239)    = " << to_dec_string(tmp) << "\n";
		ss << "Iterations 1/239 #" << iter_1_239 << "\n\n";

		ss << "Bits #" << digits << " | Decimal Digits #" << digits_dec << "\n";
		#if defined(NDEBUG)
			ss << "Trel = ";
		#else
			ss << "Tdbg = ";
		#endif
		ss << dur_us.count() << " us\n";

		#if _WIN64
			ss << "64-bit Executable\n";
		#elif _WIN32
			ss << "32-bit Executable\n";
		#else
		  #error Not recognized executable typer
		#endif

		std::cout << ss.str() << "\n";
		std::cout << "Store to Log File...\n";

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
