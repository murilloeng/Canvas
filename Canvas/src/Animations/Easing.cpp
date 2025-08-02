//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Animations/Easing.hpp"

static float value_linear(float t)
{
	return t;
}
static float value_sin_in(float t)
{
	return 1 - cosf(float(M_PI_2) * t);
}
static float value_sin_out(float t)
{
	return sinf(float(M_PI_2) * t);
}
static float value_sin_in_out(float t)
{
	return (1 - cosf(float(M_PI) * t)) / 2;
}
static float value_back_in(float t)
{
	const float c1 = 1.70158f;
	const float c3 = 2.70158f;
	return c3 * t * t * t - c1 * t * t;
}
static float value_back_out(float t)
{
	const float c1 = 1.70158f;
	const float c3 = 2.70158f;
	return 1 + c1 * powf(1 - t, 2) - c3 * powf(1 - t, 3);
}
static float value_back_in_out(float t)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;
	return t < 0.5 ? 
		4 * t * t * ((1 + c2) * t - c2 / 2) : 
		4 * (1 - t) * (1 - t) * (c2 / 2 - (1 + c2) * (1 - t)) + 1;
}
static float value_elastic_in(float t)
{
	//data
	const float c4 = 2 * float(M_PI) / 3;
	//return
	return 
		t == 0 ? 0 : 
		t == 1 ? 1 : -powf(2, 10 * t - 10) * sinf(c4 * (10 * t - 10.75f));
}
static float value_elastic_out(float t)
{
	//data
	const float c4 = 2 * float(M_PI) / 3;
	//return
	return 
		t == 0 ? 0 : 
		t == 1 ? 1 : powf(2, -10 * t) * sinf(c4 * (10 * t - 0.75f)) + 1;
}
static float value_elastic_in_out(float t)
{
	//data
	const float c5 = 4 * float(M_PI) / 9;
	const float v1 = -(powf(2, +20 * t - 10) * sinf((20 * t - 11.125f) * c5)) / 2;
	const float v2 = +(powf(2, -20 * t + 10) * sinf((20 * t - 11.125f) * c5)) / 2 + 1;
	//return
	return t == 0 ? 0 : t == 1 ? 1 : t < 0.5f ? v1 : v2;
}

namespace canvas
{
	namespace animations
	{
		//constructor
		Easing::Easing(void) : m_type{type::linear}, m_subtype{subtype::in_out}
		{
			return;
		}
	
		//destructor
		Easing::~Easing(void)
		{
			return;
		}
	
		//value
		float Easing::value(float t) const
		{
			//data
			const float s = fmaxf(fminf(t, 1), 0);
			float(*fun[])(float) = {
				value_linear, value_linear, value_linear, 
				value_sin_in, value_sin_out, value_sin_in_out,
				value_back_in, value_back_out, value_back_in_out,
				value_elastic_in, value_elastic_out, value_elastic_in_out
			};
			//return
			for(uint32_t i = 0; i < 4; i++)
			{
				if(m_type == type(i))
				{
					return fun[3 * i + uint32_t(m_subtype)](s);
				}
			}
			return 0;
		}
	}
}