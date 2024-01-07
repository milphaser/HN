//---------------------------------------------------------------------------
//  Multi-word Hamming Numbers Generator
//---------------------------------------------------------------------------
//  Calculating the maximum HN of Multi-word unsigned integer
//  {Dynamic Programming}
//	Multi-word HN Namespace ver. 0.85 & Multi-word Namespace ver.0.15
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
//const int MW_SIZE = 1;	// Multi-word Size in Double Words [ 32 bits]
//const int MW_SIZE = 2;	// Multi-word Size in Double Words [ 64 bits]
//const int MW_SIZE = 3;	// Multi-word Size in Double Words [ 96 bits]
//const int MW_SIZE = 4;	// Multi-word Size in Double Words [128 bits]
//const int MW_SIZE = 5;	// Multi-word Size in Double Words [160 bits]
//const int MW_SIZE = 6;	// Multi-word Size in Double Words [192 bits]
//const int MW_SIZE = 7;	// Multi-word Size in Double Words [224 bits]
const int MW_SIZE = 8;	// Multi-word Size in Double Words [256 bits]
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::stringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), "..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");

	std::cout << "Calculating the maximum Multi-word HN...\n\n";

	/////////////////////////////////////////////////////////////////////////
	//  1. Generate a HNS of predefined SCALE
	std::vector<MW::INT_T<MW_SIZE>> vectorHNS;			// Hamming Number Sequence
	bool boolError = false;             // generation error flag
	MW::INT_T<MW_SIZE> mwHNmax = 0;

	auto beg = std::chrono::steady_clock::now();

	while(true)
	{
		MW::INT_T<MW_SIZE> mwHN;
		if(!HN::__get_HN_nxt(vectorHNS, mwHN))
		{
			boolError = true;
			break;
		}
		else
		{
			if(mwHN > mwHNmax)
			{
				vectorHNS.push_back(mwHNmax = mwHN);
                //  Debug Screen
//				std::cout << mwHN.to_dec_string() << "\n";
//				Sleep(10);
			}
			else
				break;
		}
	}

	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);

	/////////////////////////////////////////////////////////////////////////
	//  2. Store of the HNS complemented with the newly generated HN
	std::cout << "Store to Log File...\n\n";

	std::ofstream of(fn.str());		// Output HNS file

	if(of)
	{
		for(auto& i: vectorHNS)
		{
			of << i.to_dec_string() << "\n";
		}
	}

	{
		std::stringstream ss;

		ss << "+++\n";
		ss << "HN Generator ver." << HN::ver << "\n";
		ss << "MW Namespace ver." << MW::ver << "\n";
		if(boolError)
		{
			ss << "[Error during generation]" << "\n";
		}
		ss << "Max Multi-word HN " << mwHNmax.to_dec_string() << " [" << std::to_string(mwHNmax.digits()) << " bits]\n";
		ss << "HNS Scale: " << "" << vectorHNS.size() << "\n";
		ss << "T: " << duration.count() << " ms\n";
		ss << "+++\n";

		std::cout << ss.str();
		of << ss.str();
	}

	if(of.good())
	{
		std::cout << "The HNS saved to <" << fn.str() << "> file\n\n";
	}
	else
	{
		std::cout << "Output HNS file <" << fn.str() << "> error\n\n";
	}
	of.close();

	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

