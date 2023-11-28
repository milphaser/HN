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
//  Assumptions:
//  - the input sequence is guaranteed to be of type HNS,
//    and this is not checked
//  - the members of the sequence are restricted to the positive int
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <vcl.h>
//#include <windows.h>
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
//#include <chrono>
//#include <numeric>

//#include <sstream>

//#include <iomanip>
#include <filesystem>
#include <iostream>
#include <fstream>
//---------------------------------------------------------------------------
#include "UnitHN.h"
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
//#pragma package(smart_init)

