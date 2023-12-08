//---------------------------------------------------------------------------
//  Multi-word Namespace
//  Math functionality supporting generation of Multi-word Hamming Numbers
//  ver. 0.04
//---------------------------------------------------------------------------
//	Copyright 2023 by Milen Loukantchevsky
//---------------------------------------------------------------------------
//  Status: Under Development
//---------------------------------------------------------------------------
#ifndef UnitMWH
#define UnitMWH
//---------------------------------------------------------------------------
#include <array>
#include <cstdlib>
#include <limits>
#include <sstream>
#include <string>
#include <typeinfo>
//---------------------------------------------------------------------------
namespace MW
{
	const std::string ver = "0.04";

	using UINT	= unsigned int;
	union ULL
	{
		struct
		{
			UINT lo;
			UINT hi;
		} dw;   				// double word part (2 x 32 bit)
		unsigned long long qw;	//   quad word part (1 x 64 bit)
	};

	//  Multi-word Integer Type
	template <int N>
	class INT_T
	{
	public:
		const std::string dw_separator = ":";

		static_assert(N > 0);
		std::array<UINT, N> arr;

		__fastcall INT_T(void)     		{ arr.fill(0);}
		__fastcall INT_T(std::array<UINT, N> s)	:arr(s) {}
		__fastcall INT_T(INT_T& rhs)    { arr = rhs.arr;}

		const int digits(void)    		{ return sizeof(arr) * 8;}

		INT_T& operator=(const INT_T& rhs)
		{
			arr = rhs.arr;
			return *this;
		}

		bool operator==(const INT_T& rhs)
		{
			bool boolResult = false;

			if(arr.size() == rhs.arr.size())
			{
				for(auto i = 0; i < arr.size(); i++)
				{
					if(arr[i] != rhs.arr[i])
						break;
				}
				boolResult = true;
			}

			return boolResult;
		}

		bool operator<=(const INT_T& rhs)
		{
			bool boolResult = false;

			if(arr.size() < rhs.arr.size())
				boolResult = true;
			else if(arr.size() == rhs.arr.size())
			{
				for(auto i = 0; i < arr.size(); i++)
				{
					// MS Part ---> LS Part
					if(arr[i] > rhs.arr[i])
						break;
				}
				boolResult = true;
			}

			return boolResult;
		}

		bool operator<(const INT_T& rhs)
		{
			return !(*this == rhs) && (*this <= rhs);
		}

		 /* TODO :
		INT_T operator+=(const INT_T& rhs)
		Multi-word Multiplication by Double Word
		*/

		 /* TODO :
		INT_T operator-=(const INT_T& rhs)
		Multi-word Multiplication by Double Word
		*/

		INT_T mul_2(void)
		//  Multi-word Multiplication by 2
		//  NOTE: High part of the product is truncated
		{
			INT_T<N> prod;     	// Final Product
			UINT carry = 0;     // High Part of the Partial Product

			for(auto i = 0; i < arr.size(); i++)
			{
				ULL pp;     	// Partial Product

				// MS Part <--- LS Part
				pp.dw.lo = arr[arr.size() - i - 1];
				pp.dw.hi = 0;

				pp.qw <<= 1;
				pp.qw += carry;

				prod.arr[arr.size() - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return prod;
		}

		INT_T mul_3(void)
		//  Multi-word Multiplication by 3
		//  NOTE: High part of the product is truncated
		{
			INT_T<N> prod;     	// Final Product
			UINT carry = 0;     // High Part of the Partial Product

			for(auto i = 0; i < arr.size(); i++)
			{
				ULL pp;     	// Partial Product

				// MS Part <--- LS Part
				pp.dw.lo = arr[arr.size() - i - 1];
				pp.dw.hi = 0;

				pp.qw <<= 1;
				pp.qw += arr[arr.size() - i - 1];
				pp.qw += carry;

				prod.arr[arr.size() - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return prod;
		}

		INT_T mul_5(void)
		//  Multi-word Multiplication by 5
		//  NOTE: High part of the product is truncated
		{
			INT_T<N> prod;     	// Final Product
			UINT carry = 0;     // High Part of the Partial Product

			for(auto i = 0; i < arr.size(); i++)
			{
				ULL pp;     	// Partial Product

				// MS Part <--- LS Part
				pp.dw.lo = arr[arr.size() - i - 1];
				pp.dw.hi = 0;

				pp.qw <<= 2;
				pp.qw += arr[arr.size() - i - 1];
				pp.qw += carry;

				prod.arr[arr.size() - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return prod;
		}

		 /* TODO :
		ULL mul(const INT_T& multiplier)
		Multi-word Multiplication by Double Word
		*/

		struct DIV_T
		{
			INT_T<N> quot;      // Multi-word Quotient
			UINT rem;           // Double Word Reminder
		};

		DIV_T div(const UINT divisor)
		//  Multi-word Division
		//  Multi-word Dividend/Double Word Divisor
		{
			DIV_T result;
			ULL pd = {0, 0};	// Partial Dividend

			for(auto i = 0; i < arr.size(); i++)
			{
				// MS Part ---> LS Part
				pd.dw.lo = arr[i];

				auto q = pd.qw / static_cast<unsigned long long>(divisor);
				auto r = pd.qw % divisor;

				result.quot.arr[i] = q;
				pd.dw.hi = r;
			}

			result.rem = pd.dw.hi;
			return result;
		}
	};

	template <int N>
	std::ostream& operator<<(std::ostream &os, const INT_T<N>& rhs)
	{
		os << "0x";
		auto cnt = 1;
		for(auto& i: rhs.arr)
		{
			os << std::setfill('0') << std::hex << std::uppercase
			   << std::setw(std::numeric_limits<UINT>::digits/4) << i;
			if(cnt++ < rhs.arr.size())
			  os << rhs.dw_separator;	// add double word separator
		}
		return os;
	}
}
//---------------------------------------------------------------------------
#endif

