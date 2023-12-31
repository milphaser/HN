//---------------------------------------------------------------------------
//  Multi-word Namespace
//  Math functionality supporting generation of Multi-word Hamming Numbers
//  ver. 0.19
//---------------------------------------------------------------------------
//	Copyright 2023 by Milen Loukantchevsky
//---------------------------------------------------------------------------
#ifndef UnitMWH
#define UnitMWH
//---------------------------------------------------------------------------
#include <array>
#include <vector>
#include <sstream>

#include <exception>
//---------------------------------------------------------------------------
namespace MW
{
	const std::string ver = "0.19";

	template <int N> class INT_T;

	using UINT	= unsigned int;
	union ULL
	{
		struct
		{
			UINT lo;
			UINT hi;
		} dw;   				// Double Word part (2 x 32 bit)
		unsigned long long qw;	//   Quad Word part (1 x 64 bit)
	};

	template <int N>
	struct DIV_T
	{
		INT_T<N> quot;      // Multi-word Quotient
		INT_T<N> rem;		// Multi-word Reminder
	};

	//  Multi-word Integer Type
	template <int N>
	class INT_T
	{
	public:
		static_assert(N > 0);
		std::array<UINT, N> arr;
		const std::string dw_separator = ":";

		INT_T(void) 				{arr.fill(0);}
		INT_T(const INT_T& rhs) 	{arr = rhs.arr;}
		INT_T(const UINT& rhs) 		{arr.fill(0); arr[N - 1] = rhs;}
		INT_T(const std::array<UINT, N>& s):arr(s) {}
		INT_T(const std::string& s)	{*this = s;}

		const int digits(void)		const {return (sizeof(arr) * std::numeric_limits<byte>::digits);}
		const INT_T max(void)		const {INT_T result; return result -= 1;}

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

		INT_T& operator=(const std::array<UINT, N>& rhs)
		{
			arr = rhs;
			return *this;
		}

		INT_T& operator=(const std::string& rhs)
		//  NOTE 1: The length of the source string is not controlled
		//  NOTE 2: In case of invalid argument it is omitted
		{
			arr.fill(0);
			if(rhs.find("0x") == 0)
			{   //  HEX String
				for(auto& c: rhs.substr(2))
				{
					if(std::isxdigit(c))
					{
						UINT x;
						std::stringstream ss;
						ss << c;
						ss >> std::hex >> x;
						*this <<= 4;
						*this |= x;
					}
				}
			}
			else
			{   //  DEC String
				std::string rrhs(rhs.rbegin(), rhs.rend());
				UINT p = 0;
				for(auto& c: rrhs)
				{
					if(std::isdigit(c))
					{
						INT_T dec;
						UINT x;
						std::stringstream ss;
						ss << c;
						ss >> std::dec >> x;
						dec = x;
						*this += dec.mul_10(p++);
					}
				}
			}

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

				arr[N - i - 1] = ps.dw.lo;

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

		INT_T& operator&=(const INT_T& rhs)
		{
			for(auto i = 0; i < N; i++)
				arr[i] &= rhs.arr[i];
			return *this;
		}

		INT_T& operator|=(const INT_T& rhs)
		{
			for(auto i = 0; i < N; i++)
				arr[i] |= rhs.arr[i];
			return *this;
		}

		INT_T& operator<<=(const UINT& rhs)
		{
			UINT shifts = rhs;
			if(shifts > digits()) shifts = digits();
			UINT lor = 0;			// Left Overrun of the Partial Shift

			for(auto i = 0; i < N; i++)
			{
				ULL ps = {0, 0};    // Partial Shift

				// MS Part <--- LS Part
				ps.dw.lo = arr[N - i - 1];
				ps.qw <<= shifts;
				ps.dw.lo |= lor;
				arr[N - i - 1] = ps.dw.lo;

				lor = ps.dw.hi;
			}
			return *this;
		}

		INT_T& operator>>=(const UINT& rhs)
		{
			UINT shifts = rhs;
			if(shifts > digits()) shifts = digits();
			UINT ror = 0;		// Right Overrun of the Partial Shift

			for(auto i = 0; i < N; i++)
			{
				ULL ps = {0, 0};    // Partial Shift

				// MS Part ---> LS Part
				ps.dw.hi = arr[i];
				ps.qw >>= shifts;
				ps.dw.hi |= ror;
				arr[i] = ps.dw.hi;

				ror = ps.dw.lo;
			}
			return *this;
		}

		INT_T min(const INT_T& rhs)
		{
			if(*this <= rhs)
				return *this;
			else
				return rhs;
		}

		INT_T max(const INT_T& rhs)
		{
			if(*this >= rhs)
				return *this;
			else
				return rhs;
		}

		INT_T mul_2(void)
		//  Multi-word Multiplication by 2
		//  NOTE: High part of the product is truncated
		{
			INT_T product = *this;
			UINT carry = 0;			// High Part of the Partial Product

			for(auto i = 0; i < N; i++)
			{
				ULL pp;     		// Partial Product

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
			UINT carry = 0;     	// High Part of the Partial Product

			for(auto i = 0; i < N; i++)
			{
				ULL pp;     		// Partial Product

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

		INT_T mul_10(void)
		//  Multi-word Multiplication by 10
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
				pp.qw <<= 1;

				pp.qw += carry;

				product.arr[N - i - 1] = pp.dw.lo;
				carry = pp.dw.hi;
			}

			return product;
		}

		INT_T mul_10(UINT exp)
		//  Multi-word Multiplication by (10 ** exp)
		//  NOTE: High part of the product is truncated
		{
			INT_T product = *this;
			for(auto ii = 0; ii < exp; ii++)
			{
				UINT carry = 0;     // High Part of the Partial Product

				for(auto i = 0; i < N; i++)
				{
					ULL pp;     	// Partial Product

					// MS Part <--- LS Part
					pp.dw.lo = product.arr[N - i - 1];
					pp.dw.hi = 0;

					pp.qw <<= 2;
					pp.qw += product.arr[N - i - 1];
					pp.qw <<= 1;

					pp.qw += carry;

					product.arr[N - i - 1] = pp.dw.lo;
					carry = pp.dw.hi;
				}
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

		DIV_T<N> div(const UINT& divisor)
		//  Multi-word Division
		//  Multi-word Dividend/Double Word Divisor
		{
			DIV_T<N> result;

			if(divisor == 0)
			{
				//  OVERFLOW
				result.quot -= 1;
			}
			else
			{
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

				result.rem.arr[N - 1] = pd.dw.hi;
			}
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

			DIV_T<N> q;
			q.quot = *this;
			q.rem = 0;

			while(q.quot >= radix)
			{
				q = q.quot.div(10);
				v.push_back(q.rem.arr[N - 1]);
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
	INT_T<2*N> extend(const INT_T<N>& rhs)
	//  Extend N MW rhs to 2xN MW result
	{
		INT_T<2*N> product;

		for(auto i = 0; i < N; i++)
		{
			// MS Part <--- LS Part
			product.arr[2*N - i - 1] = rhs.arr[N - i - 1];
		}

		return product;
	}

	template <int N>
	void put_hi(INT_T<2*N>& lhs, const INT_T<N>& rhs)
	//  Put <rhs> into the high part of the <lhs>
	{
		for(auto i = 0; i < N; i++)
		{
			// MS Part ---> LS Part
			lhs.arr[i] = rhs.arr[i];   		//  high part
		}
	}

	template <int N>
	INT_T<N> split_hi(const INT_T<2*N>& rhs)
	//  Split 2xN MW rhs to two N MW parts
	//  Returns:
	//  - hi, the high part;
	{
		INT_T<N> result;

		for(auto i = 0; i < N; i++)
		{
			// MS Part ---> LS Part
			result.arr[i] = rhs.arr[i];   	//  high part
		}

		return result;
	}

	template <int N>
	INT_T<N> split_lo(const INT_T<2*N>& rhs)
	//  Split 2xN MW rhs to two N MW parts
	//  Returns:
	//  - lo, the low part.
	{
		INT_T<N> result;

		for(auto i = 0; i < N; i++)
		{
			// MS Part ---> LS Part
			result.arr[i] = rhs.arr[N + i];	//  low part
		}

		return result;
	}

	template <int N>
	INT_T<2*N> mul(const INT_T<N>& multiplicand, const INT_T<N>& multiplier)
	//  Multi-word Total Multiplication
	{
		INT_T<2*N> product;
		INT_T<2*N> multiplicand_ext = extend(multiplicand);

		for(auto i = 0; i < N; i++)
		{
			INT_T<2*N> pp;			// Partial Product
			// MS Part <--- LS Part
			pp = multiplicand_ext.mul(multiplier.arr[N - i - 1]);
			pp <<= i * std::numeric_limits<byte>::digits * 4;
			product += pp;
		}

		return product;
	}

	template <int N>
	DIV_T<N> div(const INT_T<N>& dividend, const INT_T<N>& divisor)
	//  Multi-word Implementation of Long Division
	//  (Multi-word Dividend/Multi-word Divisor)
	{
		DIV_T<N> result;
		const INT_T<N> zero;

		if(static_cast<INT_T<N>>(divisor) == zero)
		{   //  Division by zero
			//  Set overflow
			result.quot = result.quot.max();
			result.rem  = result.rem.max();
		}
		else
		{
			INT_T<2*N> Dividend�xt;    	//  Dividend Extended
			Dividend�xt = extend(dividend);

			for(auto i = 0; i < dividend.digits(); i++)
			{
				result.quot <<= 1;		//	clear the next bit of the quotient
				Dividend�xt <<= 1;		//  take the next MS bit of the dividend

				INT_T<N> hi = split_hi<N>(Dividend�xt);
				if(hi >= divisor)
				{
					hi -= divisor;		//	partial dividend
					put_hi<N>(Dividend�xt, hi);

					result.quot |= 1;	//	set the next bit of the quotient
				}
			}

			//  Final Reminder
			result.rem = split_hi<N>(Dividend�xt);
		}

		return result;
	}

	template <int N>
	std::ostream& operator<<(std::ostream &os, const INT_T<N>& rhs)
	{
		os << "0x";
		auto cnt = 1;
		for(auto& i: rhs.arr)
		{
			os << std::setfill('0') << std::hex << std::uppercase
			   << std::setw(std::numeric_limits <UINT>::digits/4) << i;
			if(cnt++ < N)
			  os << rhs.dw_separator;	// add double word separator
		}
		return os;
	}
}
//---------------------------------------------------------------------------
#endif

