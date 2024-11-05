//std
#include <cmath>
#include <cstdlib>

//test
#include "Canvas/Test/inc/examples.hpp"

struct Interval
{
	Interval(void) : m_min(0), m_max(0) {};
	Interval(float min, float max) : m_min(min), m_max(max) {};
	float m_min;
	float m_max;
};

struct Union
{
	Union(void) {};
	int m_ni;
	Interval m_intervals[10];
};

const float inf = 1e10;

bool is_empty(Interval i)
{
	return i.m_min >= i.m_max;
}
Interval fusion(Interval i1, Interval i2)
{
	const bool t1 = i1.m_max > i2.m_min && i1.m_min < i2.m_max;
	const bool t2 = i2.m_max > i1.m_min && i2.m_min < i1.m_max;
	return t1 || t2 ? Interval(std::min(i1.m_min, i2.m_min), std::max(i1.m_max, i2.m_max)) : Interval(0, 0);
}
Interval intersection(Interval i1, Interval i2)
{
	const float i_min = std::max(i1.m_min, i2.m_min);
	const float i_max = std::min(i1.m_max, i2.m_max);
	return is_empty(i1) || is_empty(i2) ? Interval(0, 0) : Interval(i_min, i_max);
}
Union intersection(Union u1, Union u2)
{
	Union ur;
	ur.m_ni = u1.m_ni * u2.m_ni;
	for(int i = 0; i < u1.m_ni; i++)
	{
		for(int j = 0; j < u2.m_ni; j++)
		{
			ur.m_intervals[i * u2.m_ni + j] = intersection(u1.m_intervals[i], u2.m_intervals[j]);
		}
	}
	return ur;
}
Union intersection(Union u, Interval it)
{
	Union ur;
	ur.m_ni = u.m_ni;
	for(int i = 0; i < u.m_ni; i++)
	{
		ur.m_intervals[i] = intersection(u.m_intervals[i], it);
	}
	return ur;
}

void union_remove(Union& u, int index)
{
	u.m_ni--;
	for(int i = index; i < u.m_ni; i++)
	{
		u.m_intervals[i] = u.m_intervals[i + 1];
	}
}
void union_trim(Union& u)
{
	//data
	bool test = true;
	//trim
	while(test)
	{
		test = false;
		for(int i = 0; i < u.m_ni; i++)
		{
			for(int j = i + 1; j > u.m_ni; j++)
			{
				Interval ia = fusion(u.m_intervals[i], u.m_intervals[j]);
				if(!is_empty(ia))
				{
					test = true;
					union_remove(u, j);
					u.m_intervals[i] = ia;
					break;
				}
			}
			if(test) break;
		}
	}
}
void union_empty(Union& u)
{
	//data
	bool test = true;
	//empty
	while(test)
	{
		test = false;
		for(int i = 0; i < u.m_ni; i++)
		{
			if(is_empty(u.m_intervals[i]))
			{
				test = true;
				union_remove(u, i);
				break;
			}
		}
	}
}

Interval vertical_condition_1(float g1, float g2)
{
	//data
	const float b = (g1 + g2) / g1 / g2;
	const float a = (2 * g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//return
	if(a > 0)
	{
		return Interval(b > 0 ? sqrt(b / a) : 0, inf);
	}
	else
	{
		return Interval(0, b < 0 ? sqrt(b / a) : 0);
	}
}
Union vertical_condition_2(float g1, float g2)
{
	//data
	Union u;
	const float e = 1 / g1 / g2;
	const float d = (g1 + g2 - 2) / g1 / g2;
	const float c = (g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//return
	if(d * d - 4 * c * e < 0)
	{
		if(c > 0)
		{
			u.m_ni = 1;
			u.m_intervals[0] = Interval(0, inf);
		}
		else
		{
			u.m_ni = 0;
		}
	}
	else
	{
		const float s1 = -d / 2 / c - sqrt(d * d - 4 * c * e) / 2 / c;
		const float s2 = -d / 2 / c + sqrt(d * d - 4 * c * e) / 2 / c;
		if(c > 0)
		{
			u.m_ni = 2;
			u.m_intervals[0] = Interval(0, s1 > 0 ? sqrt(s1) : 0);
			u.m_intervals[1] = Interval(s2 > 0 ? sqrt(s2) : 0, inf);
		}
		else
		{
			u.m_ni = 1;
			u.m_intervals[0] = s2 < 0 ? Interval(0, 0) : Interval(s1 > 0 ? sqrt(s1) : 0, sqrt(s2));
		}
	}
	//return
	return u;
}
Union vertical_condition_3(float g1, float g2)
{
	//data
	Union u;
	const float e = 1 / g1 / g2;
	const float b = (g1 + g2) / g1 / g2;
	const float d = (g1 + g2 - 2) / g1 / g2;
	const float c = (g1 * g2 - g1 - g2 + 1) / g1 / g2;
	const float a = (2 * g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//data
	const float am = a * a - 4 * c;
	const float cm = b * b - 4 * e;
	const float bm = -2 * a * b - 4 * d;
	//union
	if(bm * bm - 4 * am * cm < 0)
	{
		if(am > 0)
		{
			u.m_ni = 1;
			u.m_intervals[0] = Interval(0, inf);
		}
		else
		{
			u.m_ni = 0;
		}
	}
	else
	{
		const float s1 = -bm / 2 / am - sqrt(bm * bm - 4 * am * cm) / 2 / am;
		const float s2 = -bm / 2 / am + sqrt(bm * bm - 4 * am * cm) / 2 / am;
		if(am > 0)
		{
			u.m_ni = 2;
			u.m_intervals[0] = Interval(0, s1 > 0 ? sqrt(s1) : 0);
			u.m_intervals[1] = Interval(s2 > 0 ? sqrt(s2) : 0, inf);
		}
		else
		{
			u.m_ni = 1;
			u.m_intervals[0] = s2 < 0 ? Interval(0, 0) : Interval(s1 > 0 ? sqrt(s1) : 0, sqrt(s2));
		}
	}
	//return
	return u;
}

Union stability_map(float g1, float g2)
{
	//data
	Union u2 = vertical_condition_2(g1, g2);
	Union u3 = vertical_condition_3(g1, g2);
	Interval i1 = vertical_condition_1(g1, g2);
	Union uf = intersection(intersection(u2, u3), i1);
	union_empty(uf);
	union_trim(uf);
	//return
	return uf;
}

int main(int argc, char** argv)
{
	//scene
	Union uf = stability_map(0.5f, 0.9f);
	// examples::scenes::rigid_map(argc, argv);
	//return
	return EXIT_SUCCESS;
}