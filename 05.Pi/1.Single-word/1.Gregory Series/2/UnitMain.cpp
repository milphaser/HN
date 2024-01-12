//---------------------------------------------------------------------------
//  Pi Calculation
//  Taylor Series Approximation/32 bit Integer Implementation
//---------------------------------------------------------------------------
//	Taylor Series (Madhava–Leibniz/Gregory series) Approximation
//	pi/4 = arctan(1) = Sum (-1)^i x 1/(2i + 1); i = 0, 1, 2, ...
//  pi/4 = 0.7853981634...
//
//	https://en.wikipedia.org/wiki/Leibniz_formula_for_%CF%80
//	https://r-knott.surrey.ac.uk/Fibonacci/fibpi.html#section1.3
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <tchar.h>
#pragma hdrstop
#pragma argsused

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

#include <chrono>
#include <numeric>
//------------------------------------------------------------------------------
#include "UnitMain.h"
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Pi Calculation\n";
	std::cout << "Taylor Series Approximation/32 bit Integer Implementation\n";

	std::cout << "Please, wait...\n\n";

	int intIterations = 0;
	UINT pi_qurter_approximation = 0;

	const int digits = sizeof(pi_qurter_approximation) * 8;
	const int digits_dec = digits/(10./std::log10(1024));
	const long long scale = std::pow(10, digits_dec);

	auto beg = std::chrono::steady_clock::now();

	for(auto i = 0; true; i++)
	{
		unsigned long long step = scale/(2*i + 1);

		if(step != 0)
		{
			if((i % 2) == 0)
				pi_qurter_approximation += step;
			else
				pi_qurter_approximation -= step;
		}
		else
		{
			intIterations = i;
			break;
		}
	}

	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);

	std::cout << "Pi/4 = " << "0." << pi_qurter_approximation << "\n";
	std::cout << "Iterations #" << intIterations << "\n";
	std::cout << "Bits #" << digits << " | Decimal Digits #" << digits_dec << "\n";
	std::cout << "T = " << duration.count() << " ms\n";

	std::cout << std::endl;

	system("pause");
	return 0;
}
//------------------------------------------------------------------------------

