//---------------------------------------------------------------------------
//  Hamming Numbers Generator
//  Hamming Number Namespace ver. 0.79 templatized
//---------------------------------------------------------------------------
//  {Dynamic Programming}
//---------------------------------------------------------------------------
//  Calculating the maximum HN of type integer (64 bits)
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>

#include <chrono>
#include <numeric>
//---------------------------------------------------------------------------
#include "UnitHN.h"
#include "UnitMain.h"
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::wstringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), L"..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");

	std::wcout << L"Calculating the maximum HN of type integer (64 bits)" << std::endl;
	std::wcout << L"Please, wait..." << std::endl << std::endl;

	/////////////////////////////////////////////////////////////////////////
	//  1. Generate a HNS of predefined SCALE
	std::vector<HN::LL> vectorHNS;			// Hamming Number Sequence
	bool boolError = false;             // generation error flag
	HN::LL llHNmax = 0;

	auto beg = std::chrono::steady_clock::now();

	while(true)
	{
		HN::LL llHN;
		if(!HN::__get_HN_nxt(vectorHNS, llHN))
		{
			boolError = true;
			break;
		}
		else
		{
			if(llHN > llHNmax)
			{
				vectorHNS.push_back(llHNmax = llHN);
			}
			else
			{
				break;
			}
		}
	}

	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

	/////////////////////////////////////////////////////////////////////////
	//  2. Store of the HNS complemented with the newly generated HN
	std::wofstream wof(fn.str());		// Output HNS file

	if(wof)
	{
		for(auto& i: vectorHNS)
		{
			wof << i << std::endl;
		}
	}

	{
		std::wstringstream wss;

		wss << "+++" << std::endl;
		wss << L"HN Generator ver." << HN::ver << std::endl;
		if(boolError)
		{
			wss << L"[Error during generation]" << std::endl;
		}
		wss << L"Max HN type integer (64 bits): " << llHNmax << std::endl;
		wss << L"HNS Scale: " << "" << vectorHNS.size() << std::endl;
		wss << L"T: " << duration.count() << L", microseconds" << std::endl;
		wss << "+++" << std::endl;

		wss << std::endl;

		std::wcout << wss.str();
		wof << wss.str();
	}

	if(wof.good())
	{
		std::wcout << L"The HNS saved to <" << fn.str() << L"> file" << std::endl << std::endl;
	}
	else
	{
		std::wcout << L"Output HNS file <" << fn.str() << L"> error" << std::endl << std::endl;
	}
	wof.close();

	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

