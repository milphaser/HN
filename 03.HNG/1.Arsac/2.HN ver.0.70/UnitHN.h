//---------------------------------------------------------------------------
//  Hamming Number Namespace
//  ver. 0.70
//
//	Idea of Jacques Arsac
//	Implementation 2023 by Milen Loukantchevsky
//---------------------------------------------------------------------------
#ifndef UnitHNH
#define UnitHNH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
//---------------------------------------------------------------------------
namespace HN
{
	enum class Factor
	{
		f_2 = 2, f_3 = 3, f_5 = 5
	};

	bool __get_HN_nxt(const std::vector<int>& src, int& dst);
	bool __get_HN_nxt(const std::vector<int>& src, const Factor& f, int& dst);
}
//---------------------------------------------------------------------------
#endif
