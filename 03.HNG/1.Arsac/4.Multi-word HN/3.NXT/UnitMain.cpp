//---------------------------------------------------------------------------
//  Multi-word Hamming Number Generator
//  {Dynamic Programming}
//---------------------------------------------------------------------------
//	Multi-word HN Namespace ver.0.85
//	Multi-word Namespace ver.0.18
//---------------------------------------------------------------------------
//  The Arsac's idea implementation:
//  Generating the next Hamming Number to the previously generated HNS
//
//  Input file:  Source HNS (HEX or DEC)
//  Output file: Source HNS + next HN generated
//
//  Status: Completed
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#pragma argsused
//---------------------------------------------------------------------------
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

//#include <chrono>
//#include <numeric>
//---------------------------------------------------------------------------
#include "UnitHN.h"
#include "UnitMain.h"
//---------------------------------------------------------------------------
//const int MW_SIZE = 1;	// Multi-word Size in Double Words [ 32 bits]
//const int MW_SIZE = 2;	// Multi-word Size in Double Words [ 64 bits]
//const int MW_SIZE = 3;	// Multi-word Size in Double Words [ 96 bits]
const int MW_SIZE = 4;	// Multi-word Size in Double Words [128 bits]
//const int MW_SIZE = 5;	// Multi-word Size in Double Words [160 bits]
//const int MW_SIZE = 6;	// Multi-word Size in Double Words [192 bits]
//const int MW_SIZE = 7;	// Multi-word Size in Double Words [224 bits]
//const int MW_SIZE = 8;	// Multi-word Size in Double Words [256 bits]
//const int MW_SIZE = 16;	// Multi-word Size in Double Words [512 bits]
//const int MW_SIZE = 32;	// Multi-word Size in Double Words [1024 bits]
//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Multi-word Hamming Number Generator\n";
	std::cout << "[HN Namespace ver." << HN::ver << "]\n";
	std::cout << "[MW Namespace ver." << MW::ver << "]\n\n";

	if(std::filesystem::exists(FILE_NAME_OUT))
	{
		std::filesystem::remove(FILE_NAME_IN);
		std::filesystem::rename(FILE_NAME_OUT, FILE_NAME_IN);
	}

	/////////////////////////////////////////////////////////////////////////
	//	1. Load of the previously generated HNS
	std::vector<MW::INT_T<MW_SIZE>> vectorHNS;			// Hamming Number Sequence

	std::ifstream inf(FILE_NAME_IN);	// Input HNS file
	if(inf)
	{
		std::cout << "Load the HNS from <" << FILE_NAME_IN << "> file\n";
		std::cout << "Please, wait...\n";

		std::string strLine;
		while(std::getline(inf, strLine))
		{
			MW::INT_T<MW_SIZE> mwItem(strLine);
			vectorHNS.push_back(mwItem);
		}
		inf.close();

		std::cout << "HNS items loaded: #" << vectorHNS.size() << "\n\n";
	}
	else
	{
		std::cout << "Input HNS file <" << FILE_NAME_IN << "> missing\n\n";
	}

	if(inf.bad())
	{
		std::cout << "Input HNS file <" << FILE_NAME_IN << "> error\n\n";
	}

	/////////////////////////////////////////////////////////////////////////
	//  2. Next HN generation
	MW::INT_T<MW_SIZE> mwHN;				// next HN in the HNS

	//	TODO : Generate the next HN at the end of the HNS
	if(HN::__get_HN_nxt(vectorHNS, mwHN))
	{
		std::cout << "Next HN [HEX] = " << mwHN << "\n";
		std::cout << "Next HN [DEC] = " << mwHN.to_dec_string() << "\n\n";
		vectorHNS.push_back(mwHN);

		/////////////////////////////////////////////////////////////////////////
		//  3. Store of the HNS complemented with the newly generated HN
		std::ofstream outf(FILE_NAME_OUT);	// Output HNS file

		if(outf)
		{
			for(auto& i: vectorHNS)
			{
				outf << i.to_dec_string() << "\n";
			}
		}

		if(outf.good())
		{
			std::cout << "The HNS saved to <" << FILE_NAME_OUT << "> file\n\n";
		}
		else
		{
			std::cout << "Output HNS file <" << FILE_NAME_OUT << "> error\n\n";
		}
		outf.close();
	}
	else
	{
		std::cout << "Cannot generate the next HN\n\n";
	}

	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

