//---------------------------------------------------------------------------
//  Pi Calculation
//  Taylor Series Approximation/Multi-word Implementation
//---------------------------------------------------------------------------
//	Taylor Series (Madhava–Leibniz/Gregory series) Approximation
//	pi/4 = arctan(1) = Sum (-1)^i x 1/(2i + 1); i = 0, 1, 2, ...
//  pi/4 = 0,78539816339744830961566084581988...
//
//	https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80
//	https://r-knott.surrey.ac.uk/Fibonacci/fibpi.html#section1.3
//---------------------------------------------------------------------------
//	Multi-word Namespace ver.0.21
//
//  Status: Under Development
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
const int MW_SIZE = 1;	// Multi-word Size in Double Words [ 32 bits]
//const int MW_SIZE = 2;	// Multi-word Size in Double Words [ 64 bits]
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
	ss << "Pi Calculation [Taylor Series Approximation]\n\n";
	std::cout << ss.str();

	std::cout << "Please, wait...\n\n";

	if(of)
	{
		MW::INT_T<2*MW_SIZE> pi_qurter_approximation_ext;
		MW::INT_T<MW_SIZE> scale(1);
		MW::INT_T<2*MW_SIZE> scale_ext;
		auto digits = scale.digits;
		auto digits_dec = scale.digits_dec;
		MW::put_hi<MW_SIZE>(scale_ext, scale.mul_10(digits_dec));

		auto beg = std::chrono::steady_clock::now();

		int intIterations = 0;
		MW::UINT i = 0;
		while(true)
		{
			auto step = scale_ext.div(2*i + 1);

			auto hi = MW::split_hi<MW_SIZE>(step.quot);
			if(hi != 0)
			{
				if((i % 2) == 0)
					pi_qurter_approximation_ext += step.quot;
				else
					pi_qurter_approximation_ext -= step.quot;

				i++;
			}
			else
			{
				intIterations = i;
				break;
			}
		}

		//  Round Off
		MW::INT_T<2*MW_SIZE> r("0x80000000");
		if(MW_SIZE > 1)
			r <<= (MW_SIZE - 1);

		pi_qurter_approximation_ext += r;
		auto pi_qurter_approximation = MW::split_hi<MW_SIZE>(pi_qurter_approximation_ext);

		auto end = std::chrono::steady_clock::now();
		auto dur_ms  = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);
		auto dur_sec = std::chrono::duration_cast<std::chrono::seconds>(end - beg);
		auto dur_min = std::chrono::duration_cast<std::chrono::minutes>(end - beg);

		ss << "Pi/4 = " << "0." << pi_qurter_approximation.to_dec_string() << "\n";
		ss << "Iterations #" << intIterations << "\n";
		ss << "Bits #" << digits << " | Decimal Digits #" << digits_dec << "\n";
		#if defined(NDEBUG)
			ss << "Trel = ";
		#else
			ss << "Tdbg = ";
		#endif
		ss << dur_min.count() << " min || "
		   << dur_sec.count() << " sec || "
		   << dur_ms.count() << " ms\n";

		std::cout << ss.str() << "\n";
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
