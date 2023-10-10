//---------------------------------------------------------------------------
#ifndef UnitToolsH
#define UnitToolsH
//---------------------------------------------------------------------------
#define __VER 4

#if (__VER == 1)
	//  STANDARD C MODULUS OPERATION
#elif (__VER == 2)
	//  NONSTANDARD MODULUS IMPLEMENTATION BASED ON DFA
	#define __F_235_FAST_MOD__

	#define __F_35_BE_MOD__         // Branch Elimination Technique
	#define __F_35_BE2_MOD__        // Branch Elimination Technique 2
	#if defined __F_35_BE2_MOD__
		#undef __F_35_BE_MOD__
	#endif
#elif (__VER == 3)
	//  SDT LIBRARY GCD IMPLEMENTATION
	#define __F_235_GCD__
#elif (__VER == 4)
	//  SPECIALIZED DIVISIBILITY CHECK BY 3 and 5
	#define __F_35_DIV_CHK__        //  Loop Implementation
	#define __F_35_DIV_CHK_BOOST__  //  POPCNT Implementation
	#if defined __F_35_DIV_CHK_BOOST__
		#undef __F_35_DIV_CHK__
	#endif
#else
	#error INVALID VERSION
#endif
//---------------------------------------------------------------------------
#define __F_235_PRINT__
#define __F_235_FAST_DIV__
//---------------------------------------------------------------------------
void print_header(std::wofstream& wof);

bool f_235(DWORD src, int& exp_2, int& exp_3, int& exp_5);

DWORD f_2(DWORD src, int& exp_2);
DWORD f_3(DWORD src, int& exp_3);
DWORD f_5(DWORD src, int& exp_5);

BOOL div_chk_3(DWORD src);
BOOL div_chk_5(DWORD src);

int mod_3(DWORD src);
int mod_5(DWORD src);

DWORD div_3(DWORD divident);
DWORD div_5(DWORD divident);
//---------------------------------------------------------------------------
#endif
