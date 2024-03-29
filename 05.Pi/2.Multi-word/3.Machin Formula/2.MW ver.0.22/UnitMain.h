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
	std::unique_ptr<MW::INT_T<2*N>> result = std::make_unique<MW::INT_T<2*N>>();

	std::unique_ptr<MW::INT_T<N>> scale = std::make_unique<MW::INT_T<N>>(1);
	auto digits = scale->digits;
	auto digits_dec = scale->digits_dec;

	std::unique_ptr<MW::INT_T<2*N>> scale_ext = std::make_unique<MW::INT_T<2*N>>();
	MW::put_hi<N>(*scale_ext, scale->mul_10(digits_dec));
	*scale_ext = scale_ext->div(rhs).quot;

	iter = 0;
	MW::UINT denumerator = 1;
	for(MW::UINT denumerator = 1; true; iter++, denumerator += 2)
	{
		std::unique_ptr<MW::DIV_T<2*N>> step = std::make_unique<MW::DIV_T<2*N>>(scale_ext->div(denumerator));

		bool stop = true;
		for(auto j = 0; j < N; j++)
		{
			if(step->quot.arr[j] != 0)
			{
				stop = false;
				break;
			}
		}

		if(stop)
			break;

		if((iter & 1) == 0)
			*result += step->quot;
		else
			*result -= step->quot;

		std::unique_ptr<MW::DIV_T<2*N>> tmp = std::make_unique<MW::DIV_T<2*N>>(scale_ext->div(rhs));
		*tmp = tmp->quot.div(rhs);
		*scale_ext = tmp->quot;
	}

	return *result;
}
//---------------------------------------------------------------------------
#endif

