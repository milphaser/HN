//---------------------------------------------------------------------------
//  Hamming Numbers Generator
//  {Dynamic Programming}
//---------------------------------------------------------------------------
//  The Arsac's idea implementation:
//  Generating the next Hamming Number to the previously generated HNS
//
//  Hamming Number Namespace is separated into a self contained module
//
//  Input file:  the source HNS
//  Output file: the source HNS + next HN generated
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <vcl.h>
//#include <windows.h>
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <algorithm>
//#include <chrono>
//#include <numeric>

#include <string>
//#include <sstream>
#include <vector>

//#include <iomanip>
#include <filesystem>
#include <iostream>
#include <fstream>
//---------------------------------------------------------------------------
#include "UnitMain.h"
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	if(std::filesystem::exists(FILE_NAME_OUT))
	{
		std::filesystem::remove(FILE_NAME_IN);
		std::filesystem::rename(FILE_NAME_OUT, FILE_NAME_IN);
	}

	/////////////////////////////////////////////////////////////////////////
	//	1. Load of the previously generated HNS
	std::vector<int> vectorHNS;			// Hamming Number Sequence

	std::wifstream wif(FILE_NAME_IN);	// Input HNS file
	if(wif)
	{
		std::wcout << L"Load the HNS from <" << FILE_NAME_IN << L"> file" << std::endl;

		bool boolError = false;
		wchar_t wcharLineBuf[128];
		while(wif.getline(wcharLineBuf, sizeof(wcharLineBuf)))
		{
			std::wstring wstrLineBuf = wcharLineBuf;
			try
			{
				const int intItem{std::stoi(wstrLineBuf)};
				vectorHNS.push_back(intItem);
			}
			catch (std::invalid_argument const& e)
			{
				std::wcout << "Invalid argument: " << e.what() << std::endl;
				boolError = true;
			}
			catch (std::out_of_range const& e)
			{
				std::wcout << "Out of range: " << e.what() << std::endl;
				boolError = true;
			}
		}
		wif.close();

		if(!boolError)
		{
			std::wcout << "HNS items loaded: #" << vectorHNS.size() << std::endl << std::endl;
		}
		else
		{
			std::wcout << "Generatiton aborted" << std::endl << std::endl;
			system("pause");
			return -1;
		}
	}
	else
	{
		std::wcout << L"Input HNS file <" << FILE_NAME_IN << L"> missing" << std::endl << std::endl;
	}

	if(wif.bad())
	{
		std::wcout << L"Input HNS file <" << FILE_NAME_IN << L"> error" << std::endl << std::endl;
	}

	/////////////////////////////////////////////////////////////////////////
	//  2. Next HN generation
	int intHN;							// next HN in the HNS

	//	TODO : Generate the next HN at the end of the HNS
	if(HN::__get_HN_nxt(vectorHNS, intHN))
	{
		std::wcout << L"Next HN = " << intHN << std::endl << std::endl;
		vectorHNS.push_back(intHN);

		/////////////////////////////////////////////////////////////////////////
		//  3. Store of the HNS complemented with the newly generated HN
		std::wofstream wof(FILE_NAME_OUT);	// Output HNS file

		if(wof)
		{
			for(auto& i: vectorHNS)
			{
				wof << i << std::endl;
			}
		}

		if(wof.good())
		{
			std::wcout << L"The HNS saved to <" << FILE_NAME_OUT << L"> file" << std::endl << std::endl;
		}
		else
		{
			std::wcout << L"Output HNS file <" << FILE_NAME_OUT << L"> error" << std::endl << std::endl;
		}
		wof.close();
	}
	else
	{
		std::wcout << L"Cannot generate the next HN" << std::endl << std::endl;
	}

	system("pause");
	return 0;
}
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
//#pragma package(smart_init)

