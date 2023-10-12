//---------------------------------------------------------------------------
//  Проверка за факторизация от вида (2^k)*(3^l)*(5^m),
//  където k, l и m са цели неотрицателни числа.
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>
//#include <stdio.h>

#include <iostream>
#include <iomanip>
#include <chrono>
#include <numeric>

#include <string>
#include <fstream>
#include <sstream>

#include "UnitMain.h"
//---------------------------------------------------------------------------
//const DWORD BEG = 0;
//const DWORD N 	= 64;
//const DWORD BEG = 0;
//const DWORD N 	= 1024;
//const DWORD BEG = 0xFFFFFF;
//const DWORD N 	= 0xFFFFFF;
const DWORD BEG = 0x0;
const DWORD N 	= 0xFFFFF;
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

	{
		std::wstringstream wss;

		wss << L"Checking for factorability as (2^k)*(3^l)*(5^m)" << std::endl;
		wss << L"[Version " << __VER << "]" << std::endl << std::endl;

		#if defined __F_235_FAST_MOD__
			wss << L"Fast modulus implementation" << std::endl;
			#if defined __F_35_BE_MOD__
				wss << L"[Branch Elimination Technique]" << std::endl;
			#elif defined __F_35_BE2_MOD__
				wss << L"[Branch Elimination Technique 2]" << std::endl;
			#endif
		#endif

		#if defined __F_235_GCD__
			wss << L"STD Library GCD" << std::endl;
		#endif

		#if defined __F_35_DIV_CHK__
			wss << L"Divisibility Check" << std::endl;
		#elif defined __F_35_DIV_CHK_BOOST__
			wss << L"Divisibility Check [popcnt]" << std::endl;
		#endif

		#if defined __F_235_FAST_DIV__
			wss << L"Fast division implementation" << std::endl;
		#endif

		#if !defined __F_235_PRINT__
			wss << L"Silent Mode. Timing..." << std::endl;
		#endif

		wss << std::endl;

		std::wcout << wss.str();
		wof << wss.str();
	}

	auto beg = std::chrono::steady_clock::now();

	int f_235_num = 0;

	for(DWORD num = BEG; num < BEG + N; num++)
	{
		int exp_2 = 0, exp_3 = 0, exp_5 = 0;

		bool factorizable = f_235(num, exp_2, exp_3, exp_5);

		if(factorizable)
		{
			f_235_num++;

		#if defined __F_235_PRINT__
			std::wstringstream wss;

			wss << std::uppercase;

			wss << std::dec << std::setw(5) << f_235_num << L" ";

			wss << std::dec << std::setw(10) << num;
			wss << L"[" << std::hex << std::setw(8) << std::setfill(L'0') << num << L"] ";

			wss << std::dec << exp_2 << L"," << exp_3 << L"," << exp_5;

			wss << std::endl;

			std::wcout << wss.str();
			wof << wss.str();
		#endif
		}
	}

	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - beg);

	{
		std::wstringstream wss;

		wss << std::endl;
		wss << f_235_num << L" [" << BEG << L", " << BEG + N << L"] #" << N << std::endl;
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
bool f_235(DWORD src, int& exp_2, int& exp_3, int& exp_5)
//  Checks if <src> is factorable as (2^i)*(3^j)*(5^k)
//  Returns:
//  * false/true - not factorable/factorable
//  * exp_2 - exponent of 2
//  * exp_3 - exponent of 3
//  * exp_5 - exponent of 5
{
	DWORD k_2 = 0, k_3 = 0, k_5 = 0;
	exp_2 = 0, exp_3 = 0, exp_5 = 0;

	k_2 = f_2(src, exp_2);

	if(k_2 > 1)
	{
		k_3 = f_3(k_2, exp_3);

		if(k_3 > 1)
		{
			k_5 = f_5(k_3, exp_5);
		}
	}

	return (k_2 == 1) || (k_3 == 1) || (k_5 == 1);
}
//---------------------------------------------------------------------------
DWORD f_2(DWORD src, int& exp_2)
//  Fictorizes <src> as к*(2^exp)
//  Returns:
//  * factor k
//  * exp_2 - exponent of 2
{
	exp_2 = 0;
	if(src == 0)    return 0;

	while(src != 0)
	{
		if(src & 1) break;

		exp_2++;
		src >>= 1;
	}

	return src;
}
//---------------------------------------------------------------------------
DWORD f_3(DWORD src, int& exp_3)
//  Fictorizes <src> as k*(3^exp)
//  Returns:
//  * factor k
//  * exp_3 - exponent of 3
{
	exp_3 = 0;
	if(src == 0)    return 0;

	DWORD rslt = src;

#if defined __F_35_DIV_CHK__
	while(div_chk_3(rslt) && (rslt != 1))
	{
		exp_3++;
		rslt = div_3(rslt);
	}
#elif defined __F_235_GCD__
	while((std::gcd(rslt, 3) == 3) && (rslt != 1))
	{
		exp_3++;
		rslt = div_3(rslt);
	}
#else
	while((mod_3(rslt) == 0) && (rslt != 1))
	{
		exp_3++;
		rslt = div_3(rslt);
	}
#endif

	return rslt;
}
//---------------------------------------------------------------------------
DWORD f_5(DWORD src, int& exp_5)
//  Fictorizes <src> as k*(5^exp)
//  Returns:
//  * factor k
//  * exp_5 - exponent of 5
{
	exp_5 = 0;
	if(src == 0)    return 0;

	DWORD rslt = src;

#if defined __F_35_DIV_CHK__
	while(div_chk_5(rslt) && (rslt != 1))
	{
		exp_5++;
		rslt = div_5(rslt);
	}
#elif defined __F_235_GCD__
	while((std::gcd(rslt, 5) == 5) && (rslt != 1))
	{
		exp_5++;
		rslt = div_5(rslt);
	}
#else
	while((mod_5(rslt) == 0) && (rslt != 1))
	{
		exp_5++;
		rslt = div_5(rslt);
	}
#endif

	return rslt;
}
//---------------------------------------------------------------------------
BOOL div_chk_3(DWORD src)
{
	BOOL rslt = false;

	//  Short Code Divisibility Table
	const DWORD scdt = 0x00009249;
	// FEDC BA98 7654 3210
	// 1001 0010 0100 1001

	__asm
	{
#if defined __F_35_DIV_CHK_BOOST__
		//  EAX - general buffer
		//	ECX	- cnt_odd, counter of odd bits
		//	EDX	- cnt_evn, counter of even bits

		mov EAX, [src]
		and EAX, 0x55555555 //  even bits: 0101 0101 0101 0101 0101 0101 0101 0101
		popcnt EDX, EAX

		mov EAX, [src]
		and EAX, 0xAAAAAAAA //  odd bits: 1010 1010 1010 1010 1010 1010 1010 1010
		popcnt ECX, EAX
#else
		//  EAX - general buffer
		//  EBX - modified src buffer
		//	ECX	- cnt_odd, counter of odd bits
		//	EDX	- cnt_evn, counter of even bits

		mov EBX, [src]
		xor ECX, ECX
		xor EDX, EDX

	L_BEG:
		cmp EBX, 0
		jz L_END

		mov EAX, EBX
		and EAX, 0x1
		add EDX, EAX

		mov EAX, EBX
		shr EAX, 1
		and EAX, 0x1
		add ECX, EAX

		shr EBX, 2
		jmp L_BEG

	L_END:
#endif
		//  cnt_odd - cnt_evn
		sub ECX, EDX
		mov EAX, ECX

		//  abs(cnt_odd - cnt_evn)
		cdq
		xor EAX, EDX
		sub EAX, EDX

		mov ECX, EAX

		mov EAX, [scdt]
		shr EAX, CL
		and EAX, 0x1

		mov [rslt], EAX
	}

	return rslt;
}
//---------------------------------------------------------------------------
BOOL div_chk_5(DWORD src)
{
	BOOL rslt = false;

	//  Short Code Divisibility Table
	const DWORD scdt = 0x00008421;
	// FEDC BA98 7654 3210
	// 1000 0100 0010 0001

	__asm
	{
#if defined __F_35_DIV_CHK_BOOST__
		//  EAX - general buffer
		//	ECX	- cnt_odd, counter of odd bit pairs
		//	EDX	- cnt_evn, counter of even bit pairs

		mov EAX, [src]
		and EAX, 0x22222222 //  even pairs/hi bit: 0010 0010 0010 0010 0010 0010 0010 0010
		popcnt EDX, EAX
		shl EDX, 1
		mov EAX, [src]
		and EAX, 0x11111111 //  even pairs/lo bit: 0001 0001 0001 0001 0001 0001 0001 0001
		popcnt EAX, EAX
		add EDX, EAX

		mov EAX, [src]
		and EAX, 0x88888888 //  odd pairs/hi bit: 1000 1000 1000 1000 1000 1000 1000 1000
		popcnt ECX, EAX
		shl ECX, 1
		mov EAX, [src]
		and EAX, 0x44444444 //  odd pairs/lo bit: 0100 0100 0100 0100 0100 0100 0100 0100
		popcnt EAX, EAX
		add ECX, EAX
#else
		//  EAX - general buffer
		//  EBX - modified src buffer
		//	ECX	- cnt_odd, counter of odd bits
		//	EDX	- cnt_evn, counter of even bits

		mov EBX, [src]
		xor ECX, ECX
		xor EDX, EDX

	L_BEG:
		cmp EBX, 0
		jz L_END

		mov EAX, EBX
		and EAX, 0x3
		add EDX, EAX

		mov EAX, EBX
		shr EAX, 2
		and EAX, 0x3
		add ECX, EAX

		shr EBX, 4
		jmp L_BEG

	L_END:
#endif
		//  cnt_odd - cnt_evn
		sub ECX, EDX
		mov EAX, ECX

		//  abs(cnt_odd - cnt_evn)
		cdq
		xor EAX, EDX
		sub EAX, EDX

		mov ECX, EAX

		mov EAX, [scdt]
		shr EAX, CL
		and EAX, 0x1

		mov [rslt], EAX
	}

	return rslt;
}
//---------------------------------------------------------------------------
int mod_3(DWORD src)
//  Modulus of 3
//  Returns:
//  * remainder of division by 3
{
#if defined __F_235_FAST_MOD__
	int r_3 = 0;

	if(src != 0)
	{
		DWORD mask;
		__asm
		{
			//  Get the index of the not zero MS bit
			mov EAX, [src]
			bsr EAX, EAX

			//  Set <mask> to the not zero MS bit
			mov CL, AL
			mov EAX, 1
			shl EAX, CL
			mov [mask], EAX
		}

	#if defined __F_35_BE2_MOD__
		//  Compressed Transition Table
		const DWORD tt3 = 0x00000858;
		// MSB {10 00 01} {01 10 00} LSB		<<<
		// tt3[2][3] = {{0, 2, 1}, {1, 0, 2}};	>>>
		__asm
		{
			//  Check if mask != 0
		L_LOOP:
			cmp EAX, 0
			jz L_ENDL

			//  Check if (src & mask) != 0
			and EAX, [src]
			xor EDX, EDX
			sub EDX, EAX
			sbb EAX, EAX
			and EAX, 1

			//  Pair index in tt
			//  inx = a + b
			//  a = r_3*2
			mov EDX, [r_3]
			shl EDX, 1
			//  b = 3*2*(src & mask)
			mov ECX, EAX
			shl ECX, 1
			add ECX, EAX
			shl ECX, 1
			//  a + b
			add ECX, EDX

			//  Get pair at inx
			mov EAX, [tt3]
			shr EAX, CL
			and EAX, 0x00000003
			mov [r_3], EAX

			//	mask >>= 1;
			mov EAX, [mask]
			shr EAX, 1
			mov [mask], EAX
			jmp L_LOOP
		L_ENDL:
		}
	#elif defined __F_35_BE_MOD__
		while(mask != 0)
		{
			//  Transition Table
			static int tt3[2][3] = {{0, 2, 1}, {1, 0, 2}};
			int inx = 0;
			__asm
			{
				mov EAX, [mask]
				and EAX, [src]
				//  Check if (src & mask) != 0
				xor EDX, EDX
				sub EDX, EAX
				sbb EAX, EAX
				and EAX, 1

				mov [inx], EAX
			}
			r_3 = tt3[inx][r_3];    //  Implemented with imul?!

			mask >>= 1;
		}
	#else
		while(mask != 0)
		{
			if(src & mask)
			{	//	Bit: 1
				//  Follow path 3
				if(r_3 == 1)    	r_3 = 0;
				else if(r_3 == 2)   r_3 = 2;
				else                r_3 = 1;
			}
			else
			{	// Bit: 0
				//  Follow path 3
				if(r_3 == 1)    	r_3 = 2;
				else if(r_3 == 2)   r_3 = 1;
			}

			mask >>= 1;
		}
	#endif
	}

	return r_3;
#else
	return src % 3;
#endif
}
//---------------------------------------------------------------------------
int mod_5(DWORD src)
//  Modulus of 5
//  Returns:
//  * remainder of division by 5
{
#if defined __F_235_FAST_MOD__
	int r_5 = 0;

	if(src != 0)
	{
		DWORD mask;
		__asm
		{
			//  Get the index of the not zero MS bit
			mov EAX, [src]
			bsr EAX, EAX

			//  Set <mask> to the not zero MS bit
			mov CL, AL
			mov EAX, 1
			shl EAX, CL
			mov [mask], EAX
		}

	#if defined __F_35_BE2_MOD__
		//  Compressed Transition Table
		const DWORD tt5 = 0x220CB310;
		// MSB {100 010 000 011 001} {011 001 100 010 000} LSB	<<<
		// tt5[2][5] = {{ 0, 2, 4, 1, 3}, { 1, 3, 0, 2, 4}};    >>>
		__asm
		{
			//  Check if mask != 0
		L_LOOP:
			cmp EAX, 0
			jz L_ENDL

			//  Check if (src & mask) != 0
			and EAX, [src]
			xor EDX, EDX
			sub EDX, EAX
			sbb EAX, EAX
			and EAX, 1

			//  Triple index in tt
			//  inx = a + b
			//  a = r_5*3
			mov EDX, [r_5]
			shl EDX, 1
			add EDX, [r_5]
			//  b = 5*3*(src & mask)
			mov ECX, EAX
			shl ECX, 2
			add ECX, EAX
			mov EAX, ECX
			shl ECX, 1
			add ECX, EAX
			//  a + b
			add ECX, EDX

			//  Get triple at inx
			mov EAX, [tt5]
			shr EAX, CL
			and EAX, 0x00000007
			mov [r_5], EAX

			//	mask >>= 1;
			mov EAX, [mask]
			shr EAX, 1
			mov [mask], EAX
			jmp L_LOOP
		L_ENDL:
		}
	#elif defined __F_35_BE_MOD__
		while(mask != 0)
		{
			//  Transition Table
			static int tt5[2][5] = {{ 0, 2, 4, 1, 3}, { 1, 3, 0, 2, 4}};
			int inx = 0;
			__asm
			{
				mov EAX, [mask]
				and EAX, [src]
				//  Check if (src & mask) != 0
				xor EDX, EDX
				sub EDX, EAX
				sbb EAX, EAX
				and EAX, 1

				mov [inx], EAX
			}
			r_5 = tt5[inx][r_5];    //  Implemented with imul?!

			mask >>= 1;
		}
	#else
		while(mask != 0)
		{
			if(src & mask)
			{	//	Bit: 1
				//  Follow path 5
				if(r_5 == 1)    	r_5 = 3;
				else if(r_5 == 2)   r_5 = 0;
				else if(r_5 == 3)   r_5 = 2;
				else if(r_5 == 4)   r_5 = 4;
				else                r_5 = 1;
			}
			else
			{	// Bit: 0
				//  Follow path 5
				if(r_5 == 1)    	r_5 = 2;
				else if(r_5 == 2)   r_5 = 4;
				else if(r_5 == 3)   r_5 = 1;
				else if(r_5 == 4)   r_5 = 3;
			}

			mask >>= 1;
		}
	#endif
	}

	return r_5;
#else
	return src % 5;
#endif
}
//---------------------------------------------------------------------------
DWORD div_3(DWORD divident)
//  https://stackoverflow.com/questions/20450643/division-by-3-without-division-operator?rq=3
//  Henry S. Warren, Jr. Hacker's Delight
{
#if defined __F_235_FAST_DIV__
	__int64 q = static_cast<__int64>(divident) * 0xAAAAAAAB;  // (2^33+1)/3
	return static_cast<DWORD>(q >> 33);
#else
	return std::div(divident, 3).quot;
#endif
}
//---------------------------------------------------------------------------
DWORD div_5(DWORD divident)
//  https://stackoverflow.com/questions/17113660/divisiblity-of-5-without-using-and-operator
//  Henry S. Warren, Jr. Hacker's Delight
{
#if defined __F_235_FAST_DIV__
	__int64 q = static_cast<__int64>(divident) * 0x66666667;  // (2^33+3)/5
	return static_cast<DWORD>(q >> 33);
#else
	return std::div(divident, 5).quot;
#endif
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

