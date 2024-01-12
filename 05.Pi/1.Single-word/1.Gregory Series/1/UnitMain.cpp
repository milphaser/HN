//---------------------------------------------------------------------------
//  Pi Calculation
//  Taylor Series Approximation/32 bit Integer Implementation
//---------------------------------------------------------------------------
//	Taylor Series (MadhavañLeibniz/Gregory series) Approximation
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
	std::cout << "Taylor Series Approximation/32 bit Integer Implementation\n\n";

	int intIterations = 0;
	UINT pi_qurter_approximation = 0;

	const auto digits = sizeof(pi_qurter_approximation) * 8;
	const long long digits_dec = digits/(10./std::log10(1024));
	const long long scale = std::pow(10, digits_dec);

	auto beg = std::chrono::steady_clock::now();

	for(auto i = 0; i < scale; intIterations++, i++)
	{
		if((intIterations % 2) == 0)
			pi_qurter_approximation += scale/(2*i + 1);
		else
			pi_qurter_approximation -= scale/(2*i + 1);
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
////  32 bit Long Machine Division
////  C++ Implementation
//DIV_T div(const UINT& dividend, const UINT& divisor)
////	Computes the quotient and reminder of division of the dividend by the divisor
////  Analogy to ASM version
////  - DX, dividend extended
////  - CL, divisor
////  - AX, result [AH - quotient, AL - reminder]
//{
//	DIV_T result;
//
//	if(divisor == 0)
//	{   //  Division by zero
//		//  Set overflow
//		result.quot = std::numeric_limits<UINT>::max();
//		result.rem  = std::numeric_limits<UINT>::max();
//	}
//	else
//	{
//		ULL Dividend≈xt;            	//  Dividend Extended
//		Dividend≈xt.dw.hi = 0;
//		Dividend≈xt.dw.lo = dividend;
//
//		result.quot = 0;
//
//		for(auto i = 0; i < std::numeric_limits<UINT>::digits; i++)
//		{
//			result.quot <<= 1;			//	clear the next bit of the quotient
//			Dividend≈xt.qw <<= 1;		//  take the next MS bit of the dividend
//
//			if(Dividend≈xt.dw.hi >= divisor)
//			{
//				Dividend≈xt.dw.hi -= divisor;	//	partial dividend
//				result.quot |= 1;		//	set the next bit of the quotient
//			}
//		}
//
//		//  Final Reminder
//		result.rem  = Dividend≈xt.dw.hi;
//	}
//
//   return result;
//}
//------------------------------------------------------------------------------

