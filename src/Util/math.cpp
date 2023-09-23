//std
#include <cmath>
#include <cfloat>

//canvas
#include "inc/Utils/math.hpp"

namespace canvas
{
	float norm(const float* v)
	{
		return sqrtf(inner(v, v));
	}
	float inner(const float* v1, const float* v2)
	{
		return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
	}

	float min(const float* v, unsigned* index, bool abs)
	{
		double v_min = +FLT_MAX;
		for(unsigned i = 0; i < 3; i++)
		{
			if(v_min > (abs ? fabsf(v[i]) : v[i]))
			{
				if(index) *index = i;
				v_min = abs ? fabsf(v[i]) : v[i];
			}
		}
		return v_min;
	}
	float max(const float* v, unsigned* index, bool abs)
	{
		double v_max = -FLT_MAX;
		for(unsigned i = 0; i < 3; i++)
		{
			if(v_max < (abs ? fabsf(v[i]) : v[i]))
			{
				if(index) *index = i;
				v_max = abs ? fabsf(v[i]) : v[i];
			}
		}
		return v_max;
	}

	void triad(const float* t1, float* t2, float* t3)
	{
		//data
		unsigned index;
		min(t1, &index, true);
		const unsigned k1 = (index + 1) % 3;
		const unsigned k2 = (index + 2) % 3;
		const unsigned k3 = (index + 3) % 3;
		//triad
		t2[k1] = 0;
		t2[k2] = -t1[k3] / sqrtf(t1[k2] * t1[k2] + t1[k3] * t1[k3]);
		t2[k3] = +t1[k2] / sqrtf(t1[k2] * t1[k2] + t1[k3] * t1[k3]);
		//cross
		cross(t3, t1, t2);
	}
	void cross(float* vc, const float* v1, const float* v2)
	{
		vc[0] = v1[1] * v2[2] - v1[2] * v2[1];
		vc[1] = v1[2] * v2[0] - v1[0] * v2[2];
		vc[2] = v1[0] * v2[1] - v1[1] * v2[0];
	}
}