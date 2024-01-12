//---------------------------------------------------------------------------
//  Pi Calculation
//  Taylor Series Approximation/32 bit Integer Implementation
//---------------------------------------------------------------------------
//	Taylor Series (Madhava–Leibniz/Gregory series) Approximation
//	pi/4 = arctan(1) = Sum (-1)^i x 1/(2i + 1); i = 0, 1, 2, ...
//  pi/4 = 0,78539816339744830961566084581988...
//
//	https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80
//	https://r-knott.surrey.ac.uk/Fibonacci/fibpi.html#section1.3
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <tchar.h>
#pragma hdrstop
#pragma argsused

#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>

#include <chrono>
#include <numeric>
//------------------------------------------------------------------------------
#include "UnitMain.h"
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::stringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), "..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");

	std::ofstream of(fn.str());		// Output log file
	std::stringstream ss;

	ss << "Pi Calculation\n";
	ss << "Taylor Series Approximation/32 bit Integer Implementation\n\n";
	std::cout << ss.str();

	std::cout << "Please, wait...\n\n";

	if(of)
	{
		int intIterations = 0;
		ULL pi_qurter_approximation_ext;
		pi_qurter_approximation_ext.qw = 0;

		const int digits = sizeof(UINT) * 8;
		const int digits_dec = digits/(10./std::log10(1024));
		ULL scale;
		scale.dw.hi = std::pow(10, digits_dec);

		auto beg = std::chrono::steady_clock::now();

		for(auto i = 0; true; i++)
		{
			ULL step;
			step.qw = scale.qw/(2*i + 1);

			if(step.dw.hi != 0)
			{
				if((i % 2) == 0)
					pi_qurter_approximation_ext.qw += step.qw;
				else
					pi_qurter_approximation_ext.qw -= step.qw;
			}
			else
			{
				intIterations = i;
				break;
			}
		}

		pi_qurter_approximation_ext.qw += 0x0000000080000000;   //  round off

		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);

		ss << "Pi/4 = " << "0." << pi_qurter_approximation_ext.dw.hi << "\n";
		ss << "Iterations #" << intIterations << "\n";
		ss << "Bits #" << digits << " | Decimal Digits #" << digits_dec << "\n";
		ss << "T = " << duration.count() << " ms\n";

		std::cout << ss.str() << "\n";
		of << ss.str();
	}

	if(of.good())
	{
		std::cout << "Log saved to <" << fn.str() << "> file" << std::endl;
	}
	else
	{
		std::cout << "Log file <" << fn.str() << "> error" << std::endl;
	}
	of.close();

	std::cout << std::endl;

	system("pause");
	return 0;
}
//------------------------------------------------------------------------------

