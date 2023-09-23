//std
#include <cmath>
#include <cfloat>

//canvas
#include "inc/Utils/math.hpp"

namespace canvas
{
	float fn(float t, unsigned n)
	{
		if(fabs(t) < 2 * M_PI)
		{
			return funt(t, n);
		}
		else
		{
			if(n % 2)
			{
				const unsigned p = n / 2;
				return (p % 2 ? -1 : +1) / pow(t, n) * (sin(t) - sint(t, p));
			}
			else
			{
				const unsigned p = n / 2;
				return (p % 2 ? -1 : +1) / pow(t, n) * (cos(t) - cost(t, p));
			}
		}
	}
	float dfn(float t, unsigned n)
	{
		return t * (n * fn(t, n + 2) - fn(t, n + 1));
	}
	float funt(float t, unsigned n)
	{
		//data
		int s = 1;
		unsigned k = 0;
		double v = 0, z = 1, dv;
		double p = std::tgamma(n + 1);
		//compute
		while(true)
		{
			dv = s * z / p;
			if(v + dv == v)
			{
				return v;
			}
			else
			{
				k++;
				v += dv;
				s *= -1;
				z *= t * t;
				p *= 2 * k + n;
				p *= 2 * k + n - 1;
			}
		}
	}
	float cost(float t, unsigned n)
	{
		int s = 1;
		unsigned a = 1;
		double v = 0, p = 1;
		for(unsigned k = 0; k < n; k++)
		{
			v += s * p / a;
			s *= -1;
			p *= t * t;
			a *= 2 * k + 1;
			a *= 2 * k + 2;
		}
		return v;
	}
	float sint(float t, unsigned n)
	{
		int s = 1;
		unsigned a = 1;
		double v = 0, p = t;
		for(unsigned k = 0; k < n; k++)
		{
			v += s * p / a;
			s *= -1;
			p *= t * t;
			a *= 2 * k + 2;
			a *= 2 * k + 3;
		}
		return v;
	}

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