//---------------------------------------------------------------------------
//  Hamming Number Namespace
//  ver. 0.70
//
//	Idea of Jacques Arsac
//	Implementation 2023 by Milen Loukantchevsky
//---------------------------------------------------------------------------
#include <algorithm>
//---------------------------------------------------------------------------
#include "UnitHN.h"
//---------------------------------------------------------------------------
bool HN::__get_HN_nxt(const std::vector<int>& src, int& dst)
//  Generates next HN at the end of the HNS (Arsac's Idea)
//  by merging of three HN proposal
//  Input:
//  - src, vector of the source HNS
//  - dst, generated next HN
//  Result:
//  - false, if error
//  - true, if no error
{
	int intHN_2, intHN_3, intHN_5;

	//  Generate three HN proposals
	bool boolResult = HN::__get_HN_nxt(src, HN::Factor::f_2, intHN_2);
	boolResult = boolResult && HN::__get_HN_nxt(src, HN::Factor::f_3, intHN_3);
	boolResult = boolResult && HN::__get_HN_nxt(src, HN::Factor::f_5, intHN_5);

	//  Merge the three HN proposals
	dst = std::min(intHN_2, intHN_3);
	dst = std::min(dst, intHN_5);

	return boolResult;
}
//---------------------------------------------------------------------------
bool HN::__get_HN_nxt(const std::vector<int>& src, const HN::Factor& f, int& dst)
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
	{
		dst = 1;            //  First HN
		return true;
	}

	//  Not empty source sequence
	bool boolResult = false;

	float fPreBase = src.back()/static_cast<float>(f);
	int intPreBase = std::ceil(fPreBase);

	auto it = std::find_if(src.begin(), src.end(),
		[&intPreBase](const int& item) {return item >= intPreBase;});
	if (it != src.end())
	{
		if(intPreBase == std::floor(fPreBase))
		{
			it++;
		}

		if(it != src.end())
		{
			auto aHN_Base = *it;
			dst = aHN_Base * static_cast<int>(f);
			boolResult = true;
		}
	}

	return boolResult;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
