//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
typedef struct
{
	byte quotient;  // 0xFF if divisor is zero
	byte reminder;  // 0xFF if divisor is zero
} DIV_QR;

DIV_QR __div_8_bit(byte x, byte y);	// 8 bit division
									// x - dividend
									// y - divisor
//---------------------------------------------------------------------------
#endif
