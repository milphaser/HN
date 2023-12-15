//---------------------------------------------------------------------------
//  Multi-word Hamming Number Namespace
//  ver. 0.85
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

#include "UnitMW.h"
//---------------------------------------------------------------------------
namespace HN
{
	const std::string ver = "0.85";

	enum class Factor
	{
		f_2 = 2, f_3 = 3, f_5 = 5
	};

	template <int N>
	bool __get_HN_nxt(const std::vector<MW::INT_T<N>>& src, const HN::Factor& f, MW::INT_T<N>& dst)
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
		//  Empty source sequence
		if(src.empty())
		{   //  Empty source sequence
			dst = 1;            //  First HN
			return true;
		}

		//  Not empty source sequence
		bool boolResult = false;

		auto aHN = src.back();
		auto div_t = aHN.div(static_cast<MW::UINT>(f));
		auto tBase__ = div_t.quot;	//  floor value

		bool boolDivisible = false;
		if(div_t.rem == 0)
			boolDivisible = true;   //  the last HN is divisible by the factor f
		else
			tBase__ += 1;			//  floor to ceil value

		auto it = std::find_if(src.begin(), src.end(),
							   [&tBase__](auto item) {return item >= tBase__;});
		if(it != src.end())
		{
			if(boolDivisible)
				it++;

			if(it != src.end())
			{
				auto aBase = *it;
				dst = aBase.mul(static_cast<MW::UINT>(f));
				boolResult = true;
			}
		}

		return boolResult;
	}

	template <int N>
	bool __get_HN_nxt(const std::vector<MW::INT_T<N>>& src, MW::INT_T<N>& dst)
	//  Generates next HN at the end of the HNS (Arsac's Idea)
	//  by merging of three HN proposal
	//  Input:
	//  - src, vector of the source HNS
	//  - dst, generated next HN
	//  Result:
	//  - false, if error
	//  - true, if no error
	{
		MW::INT_T<N> tHN_2, tHN_3, tHN_5;

		//  Generate three HN proposals
		bool boolResult = HN::__get_HN_nxt<N>(src, HN::Factor::f_2, tHN_2);
		boolResult = boolResult && HN::__get_HN_nxt<N>(src, HN::Factor::f_3, tHN_3);
		boolResult = boolResult && HN::__get_HN_nxt<N>(src, HN::Factor::f_5, tHN_5);

		//  Merge the three HN proposals
		dst = tHN_2.min(tHN_3);
		dst = dst.min(tHN_5);

		return boolResult;
	}
}
//---------------------------------------------------------------------------
#endif
