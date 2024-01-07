//---------------------------------------------------------------------------
//  Hamming Numbers Generator
//  Generating the next Hamming Number based on the last characteristic triplets
//---------------------------------------------------------------------------
//	Status: Abandoned
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>

#include <iostream>
#include <iomanip>
#include <chrono>
#include <numeric>

#include <string>
#include <fstream>
#include <sstream>

#include <vector>

#include "UnitMain.h"
#include "UnitTools.h"
//---------------------------------------------------------------------------
//  Current HN Triplet
DWORD triplet_base[] = {0, 1, 1};

//  Characteristic Triplets
/* TODO :
Впоследствие, характеристичните тройки да се получават автоматично,
започвайки от последното число назад */
DWORD triplets[][3] =
{
	{3, 0, 0},	//  k, 0, 0 [1 probe]
	{0, 2, 0},	//  0, l, 0 [1 probe]
	{0, 0, 1},	//  0, 0, m [1 probe]
	{2, 1, 0},	//  k, l, 0 [3 probes]
	{1, 0, 1},	//  k, 0, m [3 probes]
	{0, 1, 1},	//  0, l, m [3 probes]
	{0, 0, 0}	//  k, l, m [7 probes]
};

std::vector<DWORD> hn_probes;
//------------------------------------------------------------------------------
std::wofstream wof;         // Log file
//---------------------------------------------------------------------------
int _tmain(void)
{
	auto tp = std::chrono::system_clock::now();
	auto tt = std::chrono::system_clock::to_time_t(tp);

	std::wstringstream fn;
	// https://en.cppreference.com/w/cpp/io/manip/put_time
	fn << std::put_time(std::localtime(&tt), L"..\\..\\Logs\\Log.%Y%m%d.%H%M%S.txt");
	wof.open(fn.str());

	print_header(wof);

	auto beg = std::chrono::steady_clock::now();

	DWORD hn_base = exp_2(triplet_base[0]) * exp_3(triplet_base[1]) * exp_5(triplet_base[2]);
	print_hn(wof, hn_base, true);

	//  k, 0, 0 [1 probe]
	hn_probes.push_back(exp_2(triplets[0][0] + 1) * exp_3(triplets[0][1] + 0) * exp_5(triplets[0][2] + 0));
	//	0, l, 0 [1 probe]
	hn_probes.push_back(exp_2(triplets[1][0] + 0) * exp_3(triplets[1][1] + 1) * exp_5(triplets[1][2] + 0));
	//  0, 0, m [1 probe]
	hn_probes.push_back(exp_2(triplets[2][0] + 0) * exp_3(triplets[2][1] + 0) * exp_5(triplets[2][2] + 1));

	//  k, l, 0 [3 probes]
	hn_probes.push_back(exp_2(triplets[3][0] + 1) * exp_3(triplets[3][1] + 0) * exp_5(triplets[3][2] + 0));
	hn_probes.push_back(exp_2(triplets[3][0] + 0) * exp_3(triplets[3][1] + 1) * exp_5(triplets[3][2] + 0));
	hn_probes.push_back(exp_2(triplets[3][0] + 1) * exp_3(triplets[3][1] + 1) * exp_5(triplets[3][2] + 0));

	//  k, 0, m [3 probes]
	hn_probes.push_back(exp_2(triplets[4][0] + 1) * exp_3(triplets[4][1] + 0) * exp_5(triplets[4][2] + 0));
	hn_probes.push_back(exp_2(triplets[4][0] + 0) * exp_3(triplets[4][1] + 0) * exp_5(triplets[4][2] + 1));
	hn_probes.push_back(exp_2(triplets[4][0] + 1) * exp_3(triplets[4][1] + 0) * exp_5(triplets[4][2] + 1));

	//  0, l, m [3 probes]
	hn_probes.push_back(exp_2(triplets[5][0] + 0) * exp_3(triplets[5][1] + 1) * exp_5(triplets[5][2] + 0));
	hn_probes.push_back(exp_2(triplets[5][0] + 0) * exp_3(triplets[5][1] + 0) * exp_5(triplets[5][2] + 1));
	hn_probes.push_back(exp_2(triplets[5][0] + 0) * exp_3(triplets[5][1] + 1) * exp_5(triplets[5][2] + 1));

    //  k, l, m [7 probes]
	hn_probes.push_back(exp_2(triplets[6][0] + 1) * exp_3(triplets[6][1] + 0) * exp_5(triplets[6][2] + 0));
	hn_probes.push_back(exp_2(triplets[6][0] + 0) * exp_3(triplets[6][1] + 1) * exp_5(triplets[6][2] + 0));
	hn_probes.push_back(exp_2(triplets[6][0] + 0) * exp_3(triplets[6][1] + 0) * exp_5(triplets[6][2] + 1));
	hn_probes.push_back(exp_2(triplets[6][0] + 1) * exp_3(triplets[6][1] + 1) * exp_5(triplets[6][2] + 0));
	hn_probes.push_back(exp_2(triplets[6][0] + 1) * exp_3(triplets[6][1] + 0) * exp_5(triplets[6][2] + 1));
	hn_probes.push_back(exp_2(triplets[6][0] + 0) * exp_3(triplets[6][1] + 1) * exp_5(triplets[6][2] + 1));
	hn_probes.push_back(exp_2(triplets[6][0] + 1) * exp_3(triplets[6][1] + 1) * exp_5(triplets[6][2] + 1));

	for(auto& x: hn_probes)
	{
		print_hn(wof, x, false);
	}

	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

	{
		std::wstringstream wss;

		wss << std::endl;
//		wss << f_235_num << L" [" << BEG << L", " << BEG + N << L"] #" << N << std::endl;
		wss << L"T: " << duration.count() << L", microseconds" << std::endl;
		wss << std::endl;

		std::wcout << wss.str();
		wof << wss.str();
	}

	if(wof.good())
	{
		std::wcout << L"The Log saved to <" << fn.str() << L">" << std::endl;
	}
	wof.close();

	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
void print_hn(std::wofstream& wof, DWORD src, bool nl)
{
#if defined __F_235_PRINT__
	int exp_2 = 0, exp_3 = 0, exp_5 = 0;
	f_235(src, exp_2, exp_3, exp_5);

	std::wstringstream wss;

	wss << std::uppercase;

	wss << std::dec << std::setw(10) << src;
	wss << L"[" << std::hex << std::setw(8) << std::setfill(L'0') << src << L"] ";

	wss << std::dec << exp_2 << L"," << exp_3 << L"," << exp_5;
	wss << std::endl;

	if(nl) wss << std::endl;

	std::wcout << wss.str();
	wof << wss.str();
#endif
}
//---------------------------------------------------------------------------
DWORD exp_2(DWORD exp)
{
	DWORD rslt;

	__asm
	{
		mov EAX, 1
		mov ECX, [exp]
		cmp ECX, 0
		jz L_EXIT

		shl EAX, CL

	L_EXIT:
		mov [rslt], EAX
	}

	return rslt;
}
//---------------------------------------------------------------------------
DWORD exp_3(DWORD exp)
{
	DWORD rslt;

	__asm
	{
		mov EAX, 1
		mov ECX, [exp]
		cmp ECX, 0
		jz L_EXIT

	L_LOOP:
		mov EDX, EAX
		shl EAX, 1
		add EAX, EDX

		dec ECX
		jnz L_LOOP

	L_EXIT:
		mov [rslt], EAX
	}

	return rslt;
}
//---------------------------------------------------------------------------
DWORD exp_5(DWORD exp)
{
	DWORD rslt;

	__asm
	{
		mov EAX, 1
		mov ECX, [exp]
		cmp ECX, 0
		jz L_EXIT

	L_LOOP:
		mov EDX, EAX
		shl EAX, 2
		add EAX, EDX

		dec ECX
		jnz L_LOOP

	L_EXIT:
		mov [rslt], EAX
	}

	return rslt;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

