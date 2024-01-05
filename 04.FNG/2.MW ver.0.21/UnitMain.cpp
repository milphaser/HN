//---------------------------------------------------------------------------
//  Multi-word Fibonacci Numbers Generator
//---------------------------------------------------------------------------
//  Calculating the maximum FN of Multi-word unsigned integer
//  {Dynamic Programming}
//	Multi-word Namespace ver.0.21
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
#include "UnitMain.h"
//---------------------------------------------------------------------------
//const int MW_SIZE = 1;	// Multi-word Size in Double Words [   32 bits]
//const int MW_SIZE = 2;	// Multi-word Size in Double Words [   64 bits]
//const int MW_SIZE = 4;	// Multi-word Size in Double Words [  128 bits]
//const int MW_SIZE = 8;	// Multi-word Size in Double Words [  256 bits]
//const int MW_SIZE = 16;	// Multi-word Size in Double Words [  512 bits]
//const int MW_SIZE = 32;	// Multi-word Size in Double Words [ 1024 bits]
//const int MW_SIZE = 64;	// Multi-word Size in Double Words [ 2048 bits]
//const int MW_SIZE = 128;	// Multi-word Size in Double Words [ 4096 bits]
//const int MW_SIZE = 256;	// Multi-word Size in Double Words [ 8192 bits]
//const int MW_SIZE = 512;	// Multi-word Size in Double Words [16384 bits]
const int MW_SIZE = 1024;	// Multi-word Size in Double Words [32768 bits]
//const int MW_SIZE = 2048;	// Multi-word Size in Double Words [65536 bits]
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::stringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), "..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");

	std::cout << "Calculating the maximum Multi-word FN...\n\n";

	/////////////////////////////////////////////////////////////////////////
	//  1. Generate the FS until exhaustion of the region
	std::vector<MW::INT_T<MW_SIZE>> vectorFS;	// Fibonacci Sequence
	MW::INT_T<MW_SIZE> mwFNmax = 0;

	auto beg = std::chrono::steady_clock::now();

	while(true)
	{
		MW::INT_T<MW_SIZE> mwFN;
		mwFN = __get_FS_nxt(vectorFS);
		if(mwFN >= mwFNmax)
		{
			vectorFS.push_back(mwFNmax = mwFN);
		}
		else
			break;
	}

	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

	/////////////////////////////////////////////////////////////////////////
	//  2. Store of the FS
	std::cout << "Store to Log File...\n\n";

	std::ofstream of(fn.str());		// Output FS file

	if(of)
	{
		for(auto& i: vectorFS)
		{
			of << i.to_dec_string() << "\n";
		}
	}

	{
		std::stringstream ss;

		ss << "+++\n";
		ss << "MW Namespace ver." << MW::ver << "\n";
		ss << "Bits #" << mwFNmax.digits << "\n";
		ss << "Fractional Part Digits [DEC] #" << mwFNmax.digits_dec << "\n";
		ss << "FS Scale: " << "" << vectorFS.size() << "\n";
		ss << "Max Multi-word FN: " << mwFNmax.to_dec_string() << "\n";

		std::pair<MW::INT_T<MW_SIZE>, MW::INT_T<MW_SIZE>> ratio = __get_FS_ratio(vectorFS);
		ss << "Ratio: " << to_dec_string(ratio) << "\n";

		ss << "T: " << duration.count() << " us\n";
		ss << "+++\n";

		std::cout << ss.str();
		of << ss.str();
	}

	if(of.good())
	{
		std::cout << "The FS saved to <" << fn.str() << "> file\n\n";
	}
	else
	{
		std::cout << "Output FS file <" << fn.str() << "> error\n\n";
	}
	of.close();

	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

