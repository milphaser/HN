//---------------------------------------------------------------------------
//  Hamming Numbers Generator
//  Hamming Number Namespace ver. 0.78 templatized
//---------------------------------------------------------------------------
//  Generating the first N Hamming Numbers, where N is a predefined value
//  {Dynamic Programming}
//
//  Assumptions:
//  - the members of the sequence are restricted to the positive long long (64 bits)
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
	fn << std::put_time(std::localtime(&tt), L"..\\..\\Logs\\Log.%Y%m%d.%H%M%S.#")
	   << SCALE << ".txt";

	std::wcout << L"HN Namespace ver." << HN::ver() << std::endl;
	std::wcout << L"NHS of Scale #" << SCALE << std::endl;
	std::wcout << L"Generation in progress..." << std::endl << std::endl;

	/////////////////////////////////////////////////////////////////////////
	//  1. Generate a HNS of predefined SCALE
	std::vector<long long> vectorHNS;		// Hamming Number Sequence
	bool boolError = false;             // generation error flag

	auto beg = std::chrono::steady_clock::now();

	for(auto i = 0; i < SCALE; i++)
	{
		long long int64HN;
		if(!HN::__get_HN_nxt(vectorHNS, int64HN))
		{
			boolError = true;
			break;
		}
		vectorHNS.push_back(int64HN);
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
		wss << L"HN Generator ver." << HN::ver() << std::endl;
		wss << L"HNS of Scale #" << vectorHNS.size() << std::endl;
		if(boolError)
		{
			wss << L"[Error during generation]" << std::endl;
		}
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

