//---------------------------------------------------------------------------
#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include "UnitMW.h"
//---------------------------------------------------------------------------
template <int N>
MW::INT_T<2*N> gregory_arctan(const MW::UINT& rhs, MW::UINT& iter)
//  Returns arctan(1/rhs)
//  Uses Gregory's Series: arctan(x) = x - x^3/3 + x^5/5 - x^7/7 + ...
//  Restriction: 0 < x <= 1
//	As x decreases, the efficiency increases,
//	i.e. it is recommended x << 1
{
	MW::INT_T<2*N> result;

	MW::INT_T<N> scale(1);
	auto digits = scale.digits;
	auto digits_dec = scale.digits_dec;

	MW::INT_T<2*N> scale_ext;
	MW::put_hi<N>(scale_ext, scale.mul_10(digits_dec));
	scale_ext = scale_ext.div(rhs).quot;

	iter = 0;
	MW::UINT denumerator = 1;
	for(MW::UINT denumerator = 1; true; iter++, denumerator += 2)
	{
		auto step = scale_ext.div(denumerator);

		bool stop = true;
		for(auto j = 0; j < N; j++)
		{
			if(step.quot.arr->at(j) != 0)
			{
				stop = false;
				break;
			}
		}

		if(stop)
			break;

		if((iter & 1) == 0)
			result += step.quot;
		else
			result -= step.quot;

		scale_ext = scale_ext.div(rhs).quot;
		scale_ext = scale_ext.div(rhs).quot;
	}

	return result;
}
//---------------------------------------------------------------------------
#endif

