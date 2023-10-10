//---------------------------------------------------------------------------
//  Целочислено деление с синструкция DIV на x86
//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include <tchar.h>
//#include <stdio.h>

#include <iostream>
#include <iomanip>
//#include <chrono>
//#include <string>		// included to be able to put std::string into std::cout

#include "UnitMain.h"
//---------------------------------------------------------------------------
const DWORD BEG = 0;
const DWORD N 	= 16;
//---------------------------------------------------------------------------
int _tmain(void)
{
	std::cout << "Integer Division" << std::endl;
	std::cout << "(x86 div instruction implementation)" << std::endl << std::endl;

	for(DWORD i = BEG; i < BEG + N; i++)
	{
		DWORD q_3, r_3, q_5, r_5;
		q_3 = __div(i, 3, r_3);
		q_5 = __div(i, 5, r_5);

		std::cout << std::uppercase;

		std::cout << std::dec << std::setw(3) << std::setfill(' ') << i;
		std::cout << "[" << std::hex << std::setw(4) << std::setfill('0') << i << "]";

		std::cout << std::dec << std::setw(3) << std::setfill(' ');
		std::cout << " " << q_3 << "|" << r_3;
		std::cout << " " << q_5 << "|" << r_5;

		std::cout << std::endl;
	}

	std::cout << std::endl;
	system("pause");
	return 0;
}
//---------------------------------------------------------------------------
DWORD __div(DWORD divident, DWORD divisor, DWORD& remainder)
//  Integer Division
//  Returns:
//  * quotient
//  * remainder
//  USE STANDARD COMPILER
{
	DWORD quotient;

	__asm
	{
		//	EAX - divident (low 32 bits)/quotient
		//	ECX - divisor
		//	EDX - divident (high 32 bits)/remainder
		//  ESI - address of remainder

		push ESI

		xor EDX, EDX            // clear high 32 bits of the divident
		mov EAX, [divident]     // set low 32 bits of the divident
		mov ECX, [divisor]      // set divider

		div ECX                 // EAX <- quotient(EDX:EAX / EBX)
								// EDX <- remainder(EDX:EAX / EBX)

		mov ESI, [remainder]
		mov [ESI], EDX

		mov [quotient], EAX

        pop ESI
	}

	return quotient;
}
//---------------------------------------------------------------------------
//#pragma package(smart_init)

