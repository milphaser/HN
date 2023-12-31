//---------------------------------------------------------------------------
//  Hamming Number Namespace
//  ver. 0.79
//  (templatized)
//---------------------------------------------------------------------------
//	Idea of Jacques Arsac
//	Implementation 2023 by Milen Loukantchevsky
//---------------------------------------------------------------------------
#ifndef UnitHNH
#define UnitHNH
//---------------------------------------------------------------------------
#include <algorithm>
#include <string>
#include <vector>
//---------------------------------------------------------------------------
namespace HN
{
	using UINT = unsigned int;
	using LL = long long;
	using ULL = unsigned long long;

	const std::wstring ver = L"0.79";

	enum class Factor
	{
		f_2 = 2, f_3 = 3, f_5 = 5
	};

	//  Check if T is accepted typename
	template<typename T>
	constexpr bool strict(void)
	{
		return (std::is_same<T, int>::value || std::is_same<T, UINT>::value ||
		   std::is_same<T, LL>::value || std::is_same<T, ULL>::value);
	}

	template<typename T>
	bool __get_HN_nxt(const std::vector<T>& src, const HN::Factor& f, T& dst)
	//  Generates a proposal of the next HN (Arsac's Idea)
	//  by one of the three factors (2, 3 or 5)
	//  Input:
	//  - src, vector of the source HNS
	//  -   f, factor 2, 3 or 5
	//  - dst, generated next HN
	//  Result:
	//  - false, if error
	//  - true, if no error
	{
		if constexpr (strict<T>())
		{
			//  Empty source sequence
			if(src.empty())
			{   //  Empty source sequence
				dst = 1;            //  First HN
				return true;
			}

			//  Not empty source sequence
			bool boolResult = false;

			auto aHN = src.back();
			T tBase__ = aHN/static_cast<T>(f);      //  floor value

			bool boolDivisible = false;
			if(aHN == tBase__ * static_cast<T>(f))
			{
				boolDivisible = true;   //  the last HN is divisible by the factor f
			}
			else
			{
				tBase__++;                          //  floor to ceil value
			}

			auto it = std::find_if(src.begin(), src.end(),
				[&tBase__](const T& item) {return item >= tBase__;});
			if (it != src.end())
			{
				if(boolDivisible)
				{
					it++;
				}

				if(it != src.end())
				{
					auto aBase = *it;
					dst = aBase * static_cast<T>(f);
					boolResult = true;
				}
			}

			return boolResult;
		}
		else
		{
			return false;
        }
	}

	template<typename T>
	bool __get_HN_nxt(const std::vector<T>& src, T& dst)
	//  Generates next HN at the end of the HNS (Arsac's Idea)
	//  by merging of three HN proposal
	//  Input:
	//  - src, vector of the source HNS
	//  - dst, generated next HN
	//  Result:
	//  - false, if error
	//  - true, if no error
	{
		T tHN_2, tHN_3, tHN_5;

		//  Generate three HN proposals
		bool boolResult = HN::__get_HN_nxt(src, HN::Factor::f_2, tHN_2);
		boolResult = boolResult && HN::__get_HN_nxt(src, HN::Factor::f_3, tHN_3);
		boolResult = boolResult && HN::__get_HN_nxt(src, HN::Factor::f_5, tHN_5);

		//  Merge the three HN proposals
		dst = std::min(tHN_2, tHN_3);
		dst = std::min(dst, tHN_5);

		return boolResult;
	}
}
//---------------------------------------------------------------------------
#endif
