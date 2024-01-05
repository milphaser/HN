//---------------------------------------------------------------------------
#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------

#include "UnitMW.h"
//---------------------------------------------------------------------------
template <int N>
MW::INT_T<N> __get_FS_nxt(std::vector<MW::INT_T<N>>& vectorFS)
//  Given: FS = {F0, F1, F2, ..., Fi}
//	Where F0 = F1 = 1; Fn = F(n-1) + F(n-2) for all n >= 2.
//  Returns: The next Fibonacci Number F(i+1)
{
	MW::INT_T<N> mwFN;

	if((vectorFS.size() == 0) || (vectorFS.size() == 1))
	{
		mwFN = 1;
	}
	else
	{
		mwFN = vectorFS[vectorFS.size() - 1];
		auto mwFN2 = vectorFS[vectorFS.size() - 2];
		mwFN += mwFN2;
	}

	return mwFN;
}
//---------------------------------------------------------------------------
template <int N>
std::pair<MW::INT_T<N>, MW::INT_T<N>> __get_FS_ratio(std::vector<MW::INT_T<N>>& vectorFS)
//  Given: FS = {F0, F1, F2, ..., F(n-2), F(n-1)}
//	Calculates: Ratio = F(n-1)/F(n-2)
//  Returns:
//  - first, integer part of the ratio
//  - second, fractional part of the ratio
{
	std::pair<MW::INT_T<N>, MW::INT_T<N>> ratio;
	ratio.first = 0;
	ratio.second = 0;

	if(vectorFS.size() > 2)
	{
		auto mwFN1 = vectorFS[vectorFS.size() - 1];
		auto mwFN2 = vectorFS[vectorFS.size() - 2];

		ratio = MW::div_fp(mwFN2, mwFN1);
	}

	return ratio;
}
//---------------------------------------------------------------------------
#endif
