//---------------------------------------------------------------------------
//  Multi-word Namespace
//  Math functionality supporting generation of Multi-word Hamming Numbers
//  ver. 0.15
//---------------------------------------------------------------------------
//	Copyright 2023 by Milen Loukantchevsky
//---------------------------------------------------------------------------
#ifndef UnitMWH
#define UnitMWH
//---------------------------------------------------------------------------
#include <array>
#include <sstream>
#include <vector>
//---------------------------------------------------------------------------
namespace MW
{
	const std::string ver = "0.15";
	template <int N> class INT_T;

	using UINT	= unsigned int;
	union ULL
	{
		struct
		{
			UINT lo;
			UINT hi;
		} dw;   				// Double Word part (2 x 32 bit)
		unsigned long long qw;	// Quad Word part (1 x 64 bit)
	};

	//  Multi-word Integer Type
	template <int N>
	class INT_T
	{
	public:
		static_assert(N > 0);
		std::array<UINT, N> arr;
		const std::string dw_separator = ":";

		__fastcall INT_T(void) {arr.fill(0);}
		__fastcall INT_T(const std::array<UINT, N> s):arr(s) {}
		__fastcall INT_T(const INT_T& rhs) {arr = rhs.arr;}
		__fastcall INT_T(const UINT& rhs) {arr.fill(0); arr[N - 1] = rhs;}

		constexpr int digits(void) {return (sizeof(arr) * 8);}

		INT_T& operator=(const INT_T& rhs)
		{
			arr = rhs.arr;
			return *this;
		}

		INT_T& operator=(const UINT& rhs)
		{
			arr.fill(0);
			arr[N - 1] = rhs;
			return *this;
		}

		INT_T& operator=(const std::array<UINT, N> rhs)
		{
			arr = rhs;
			return *this;
		}

		bool operator==(const INT_T& rhs)
		{
			for(auto i = 0; i < N; i++)
			{
				if(arr[i] != rhs.arr[i])
					return false;
			}
			return true;
		}

		bool operator!=(const INT_T& rhs)
		{
			return !(*this == rhs);
		}

		bool operator<(const INT_T& rhs)
		{
			for(auto i = 0; i < N; i++)
			{
				// MS Part ---> LS Part
				if (arr[i] < rhs.arr[i])
					return true;
				else if (arr[i] > rhs.arr[i])
					return false;
			}
			return false;
		}

		bool operator>(const INT_T& rhs)
		{
			return !((*this < rhs) || (*this == rhs));
		}

		bool operator<=(const INT_T& rhs)
		{
			return !(*this > rhs);
		}

		bool operator>=(const INT_T& rhs)
		{
			return !(*this < rhs);
		}

		INT_T& operator+=(const INT_T& rhs)
		//  NOTE: Output Carry is ignored
		{
			ULL ps = {0, 0};	// Partial Sum

			for(auto i = 0; i < N; i++)
			{
				// MS Part <--- LS Part
				ps.qw += arr[N - i - 1];
				ps.qw += rhs.arr[N - i - 1];

				arr[N - i - 1] = ps.qw;

				ps.qw >>= std::numeric_limits<UINT>::digits;
			}

			return *this;
		}

		INT_T& operator+=(const UINT& rhs)
		//  NOTE: Output Carry is ignored
		{
			INT_T<N> addend = rhs;
			*this += addend;
			return *this;
		}

		INT_T& operator-=(const INT_T& rhs)
		//  NOTE: If minuend is less then subtrahend,
		//	the difference is 2's Complement coded.
		{
			//  1. Convert (-rhs) to 2's Complement Code
			INT_T<N> subtrahend;
			//  1.1. 1's Complement
			for(auto i = 0; i < N; i++)
			{
				subtrahend.arr[i] = ~rhs.arr[i];
			}
			//  1.2.    2's Complement
			subtrahend += 1;

			//  2. x = x + (-y)
			*this += subtrahend;

			return *this;
		}

		INT_T& operator-=(const UINT& rhs)
		//  NOTE: If minuend is less then subtrahend,
		//	the difference is 2's Complement coded.
		{
			INT_T<N> subtrahend = rhs;
			*this -= subtrahend;
			return *this;
		}

		INT_T min(const INT_T& rhs)
		{
			if(*this <= rhs)
				return *this;
			else
				return rhs;
		}

		INT_T mul_2(void)
		//  Multi-word Multiplication by 2
		//  NOTE: High part of the product is truncated
		{
			INT_T product = *this;
			UINT carry = 0;     // High Part of the Partial Product

			for(auto i = 0; i < N; i++)
			{
				ULL pp;     	// Partial Product

				// MS Part <--- LS Part
				pp.dw.lo = product.arr[N - i - 1];
				pp.dw.hi = 0;

				pp.qw <<= 1;
				pp.qw += carry;

				product.arr[N - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return product;
		}

		INT_T mul_3(void)
		//  Multi-word Multiplication by 3
		//  NOTE: High part of the product is truncated
		{
			INT_T product = *this;
			UINT carry = 0;     // High Part of the Partial Product

			for(auto i = 0; i < N; i++)
			{
				ULL pp;     	// Partial Product

				// MS Part <--- LS Part
				pp.dw.lo = product.arr[N - i - 1];
				pp.dw.hi = 0;

				pp.qw <<= 1;
				pp.qw += product.arr[N - i - 1];
				pp.qw += carry;

				product.arr[N - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return product;
		}

		INT_T mul_5(void)
		//  Multi-word Multiplication by 5
		//  NOTE: High part of the product is truncated
		{
			INT_T product = *this;
			UINT carry = 0;     // High Part of the Partial Product

			for(auto i = 0; i < N; i++)
			{
				ULL pp;     	// Partial Product

				// MS Part <--- LS Part
				pp.dw.lo = product.arr[N - i - 1];
				pp.dw.hi = 0;

				pp.qw <<= 2;
				pp.qw += product.arr[N - i - 1];
				pp.qw += carry;

				product.arr[N - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return product;
		}

		INT_T mul(const UINT& multiplier)
		//  Multi-word Multiplication with Double Word Multiplier
		//  NOTE: High part of the product is truncated
		{
			INT_T product = *this;
			UINT carry = 0;     	// High Part of the Partial Product

			for(auto i = 0; i < N; i++)
			{
				ULL pp = {0, 0};	// Partial Product

				// MS Part <--- LS Part
				pp.dw.lo = arr[N - i - 1];
				pp.dw.hi = 0;

				pp.qw = pp.qw * multiplier;
				pp.qw += carry;

				product.arr[N - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return product;
		}

		struct DIV_T
		{
			INT_T<N> quot;      // Multi-word Quotient
			UINT rem;           // Double Word Reminder
		};

		DIV_T div(const UINT& divisor)
		//  Multi-word Division
		//  Multi-word Dividend/Double Word Divisor
		{
			DIV_T result;
			ULL pd = {0, 0};	// Partial Dividend

			for(auto i = 0; i < N; i++)
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

		std::string to_hex_string(void)
		{
			std::stringstream oss;
			auto cnt = 1;
			for(auto& i: arr)
			{
				oss << std::setfill('0') << std::hex << std::uppercase
					<< std::setw(std::numeric_limits<UINT>::digits/4) << i;
				if(cnt++ < N)
				{
					oss << dw_separator;	// add double word separator
				}
			}
			return oss.str();
		}

		std::string to_dec_string(void)
		{
			std::vector<UINT> v;

			const INT_T radix = 10;     // Decimal Number System Radix

			DIV_T q;
			q.quot = *this;
			q.rem = 0;

			while(q.quot >= radix)
			{
				q = q.quot.div(10);
				v.push_back(q.rem);
			}
			v.push_back(q.quot.arr[N - 1]);

			std::stringstream oss;
			for(std::vector<UINT>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
			{
				oss << *it;
			}

			return oss.str();
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
			if(cnt++ < N)
			  os << rhs.dw_separator;	// add double word separator
		}
		return os;
	}
}
//---------------------------------------------------------------------------
#endif


