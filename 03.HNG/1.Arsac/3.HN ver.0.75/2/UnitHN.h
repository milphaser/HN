//---------------------------------------------------------------------------
//  Hamming Number Namespace
//  ver. 0.76
//  templatized
//
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
	enum class Factor
	{
		f_2 = 2, f_3 = 3, f_5 = 5
	};

	const std::wstring inline ver(void)     {return L"0.76";}

	template<class T> bool __get_HN_nxt(const std::vector<T>& src, const HN::Factor& f, T& dst)
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
		T tPreBase = std::ceil(fPreBase);

		auto it = std::find_if(src.begin(), src.end(),
			[&tPreBase](const T& item) {return item >= tPreBase;});
		if (it != src.end())
		{
			if(tPreBase == std::floor(fPreBase))
			{   //  the last HN is divisible by the factor f
				it++;
			}

			if(it != src.end())
			{
				auto aHN_Base = *it;
				dst = aHN_Base * static_cast<T>(f);
				boolResult = true;
			}
		}

		return boolResult;
	}

	template<class T> bool __get_HN_nxt(const std::vector<T>& src, T& dst)
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
