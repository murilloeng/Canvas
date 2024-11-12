#version 460 core

uniform float bt;
uniform float wp;
uniform uint full;
uniform uint mode;
uniform uint width;
uniform uint height;

out vec4 fragment_color;

struct Interval
{
	float m_min;
	float m_max;
};

struct Union
{
	int m_ni;
	Interval m_intervals[10];
};

const float inf = 1.00e15;

bool is_empty(Interval interval)
{
	return interval.m_min >= interval.m_max || interval.m_max - interval.m_min < 1e-5 * max(abs(interval.m_min), abs(interval.m_max));
}
Interval fusion(Interval i1, Interval i2)
{
	const bool t1 = i1.m_max > i2.m_min && i1.m_min < i2.m_max;
	const bool t2 = i2.m_max > i1.m_min && i2.m_min < i1.m_max;
	return t1 || t2 ? Interval(min(i1.m_min, i2.m_min), max(i1.m_max, i2.m_max)) : Interval(0, 0);
}
Interval intersection(Interval i1, Interval i2)
{
	const float i_min = max(i1.m_min, i2.m_min);
	const float i_max = min(i1.m_max, i2.m_max);
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

void union_remove(inout Union u, int index)
{
	u.m_ni--;
	for(int i = index; i < u.m_ni; i++)
	{
		u.m_intervals[i] = u.m_intervals[i + 1];
	}
}
void union_trim_fusion(inout Union u)
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
void union_trim_empty(inout Union u)
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

Union vertical_condition_1(float g1, float g2)
{
	//data
	Union ur;
	ur.m_ni = 1;
	const float b = (g1 + g2) / g1 / g2;
	const float a = (2 * g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//return
	if(a > 0)
	{
		ur.m_intervals[0] = Interval(b > 0 ? sqrt(b / a) : 0, inf);
	}
	else
	{
		ur.m_intervals[0] = Interval(0, b < 0 ? sqrt(b / a) : 0);
	}
	//return
	return ur;
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
			u.m_intervals[0] = s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? sqrt(s2) : 0, sqrt(s1));
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
			u.m_intervals[0] = s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? sqrt(s2) : 0, sqrt(s1));
		}
	}
	//return
	return u;
}

vec4 vertical_full(float g1, float g2)
{
	//data
	Union u1 = vertical_condition_1(g1, g2);
	Union u2 = vertical_condition_2(g1, g2);
	Union u3 = vertical_condition_3(g1, g2);
	Union uf = intersection(u1, intersection(u2, u3));
	//trim
	union_trim_empty(uf);
	union_trim_fusion(uf);
	//data
	if(uf.m_ni == 0) return vec4(1, 0, 0, 1);
	if(uf.m_ni == 1 && uf.m_intervals[0].m_max == inf) return vec4(0, 0, 1, 1);
	if(uf.m_ni == 1 && uf.m_intervals[0].m_max != inf) return vec4(1, 0.5, 0, 1);
	return vec4(1, 0, 1, 1);
}

Union tilted_1_condition_1(float g1, float g2)
{
	//data
	Union ur;
	ur.m_ni = 1;
	const float a = 2 - g2 * (1 + g1 - g2) / g1;
	const float b = (1 - 2 * g1 - g2 * (1 + g1 - g2)) / g1 / g2 / (1 - g2);
	//union
	if(a < 0)
	{
		ur.m_intervals[0] = Interval(0, b < 0 ? 0 : pow(-b / a, 0.25));
	}
	else
	{
		ur.m_intervals[0] = Interval(b > 0 ? 0 : pow(-b / a, 0.25), inf);
	}
	//return
	return ur;
}
Union tilted_1_condition_2(float g1, float g2)
{
	//data
	Union u;
	const float c = (g1 - g2) * (1 - g2) / g1;
	const float d = (g1 - g2) * (2 * g2 - 3) / g1 / g2 / (1 - g2);
	const float e = 3 * (g1 - g2) / g1 / g2 / (1 - g2) / (1 - g2);
	//union
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
			u.m_intervals[0] = Interval(0, s1 > 0 ? pow(s1, 0.25) : 0);
			u.m_intervals[1] = Interval(s2 > 0 ? pow(s2, 0.25) : 0, inf);
		}
		else
		{
			u.m_ni = 1;
			u.m_intervals[0] = s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? pow(s2, 0.25) : 0, pow(s1, 0.25));
		}
	}
	//return
	return u;
}
Union tilted_1_condition_3(float g1, float g2)
{
	//data
	Union u;
	const float c = (g1 - g2) * (1 - g2) / g1;
	const float a = 2 - g2 * (1 + g1 - g2) / g1;
	const float d = (g1 - g2) * (2 * g2 - 3) / g1 / g2 / (1 - g2);
	const float e = 3 * (g1 - g2) / g1 / g2 / (1 - g2) / (1 - g2);
	const float b = (1 - 2 * g1 - g2 * (1 + g1 - g2)) / g1 / g2 / (1 - g2);
	//data
	const float am = a * a - 4 * c;
	const float cm = b * b - 4 * e;
	const float bm = 2 * a * b - 4 * d;
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
			u.m_intervals[0] = Interval(0, s1 > 0 ? pow(s1, 0.25) : 0);
			u.m_intervals[1] = Interval(s2 > 0 ? pow(s2, 0.25) : 0, inf);
		}
		else
		{
			u.m_ni = 1;
			u.m_intervals[0] = s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? pow(s2, 0.25) : 0, pow(s1, 0.25));
		}
	}
	//return
	return u;
}

vec4 tilted_1_full(float g1, float g2)
{
	//data
	Union u1 = tilted_1_condition_1(g1, g2);
	Union u2 = tilted_1_condition_2(g1, g2);
	Union u3 = tilted_1_condition_3(g1, g2);
	//union
	Union uf = u1;
	uf = intersection(uf, u2);
	uf = intersection(uf, u3);
	uf = intersection(uf, Interval(1 / sqrt(1 - g2), inf));
	//trim
	union_trim_empty(uf);
	union_trim_fusion(uf);
	//data
	if(uf.m_ni == 0) return vec4(1, 0, 0, 1);
	if(uf.m_ni == 1 && uf.m_intervals[0].m_max == inf) return vec4(0, 0, 1, 1);
	if(uf.m_ni == 1 && uf.m_intervals[0].m_max != inf) return vec4(1, 0.5, 0, 1);
	return vec4(1, 0, 1, 1);
}

Union tilted_2_condition_1(float g1, float g2)
{
	//data
	Union ur;
	ur.m_ni = 1;
	const float a = 2 - g1 * (1 + g2 - g1) / g2;
	const float b = (1 - 2 * g2 - g1 * (1 + g2 - g1)) / g2 / g1 / (1 - g1);
	//union
	if(a < 0)
	{
		ur.m_intervals[0] = Interval(0, b < 0 ? 0 : pow(-b / a, 0.25));
	}
	else
	{
		ur.m_intervals[0] = Interval(b > 0 ? 0 : pow(-b / a, 0.25), inf);
	}
	//return
	return ur;
}
Union tilted_2_condition_2(float g1, float g2)
{
	//data
	Union u;
	const float c = (g2 - g1) * (1 - g1) / g2;
	const float d = (g2 - g1) * (2 * g1 - 3) / g2 / g1 / (1 - g1);
	const float e = 3 * (g2 - g1) / g2 / g1 / (1 - g1) / (1 - g1);
	//union
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
			u.m_intervals[0] = Interval(0, s1 > 0 ? pow(s1, 0.25) : 0);
			u.m_intervals[1] = Interval(s2 > 0 ? pow(s2, 0.25) : 0, inf);
		}
		else
		{
			u.m_ni = 1;
			u.m_intervals[0] = s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? pow(s2, 0.25) : 0, pow(s1, 0.25));
		}
	}
	//return
	return u;
}
Union tilted_2_condition_3(float g1, float g2)
{
	//data
	Union u;
	const float c = (g2 - g1) * (1 - g1) / g2;
	const float a = 2 - g1 * (1 + g2 - g1) / g2;
	const float d = (g2 - g1) * (2 * g1 - 3) / g2 / g1 / (1 - g1);
	const float e = 3 * (g2 - g1) / g2 / g1 / (1 - g1) / (1 - g1);
	const float b = (1 - 2 * g2 - g1 * (1 + g2 - g1)) / g2 / g1 / (1 - g1);
	//data
	const float am = a * a - 4 * c;
	const float cm = b * b - 4 * e;
	const float bm = 2 * a * b - 4 * d;
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
			u.m_intervals[0] = Interval(0, s1 > 0 ? pow(s1, 0.25) : 0);
			u.m_intervals[1] = Interval(s2 > 0 ? pow(s2, 0.25) : 0, inf);
		}
		else
		{
			u.m_ni = 1;
			u.m_intervals[0] = s1 < 0 ? Interval(0, 0) : Interval(s2 > 0 ? pow(s2, 0.25) : 0, pow(s1, 0.25));
		}
	}
	//return
	return u;
}

vec4 tilted_2_full(float g1, float g2)
{
	//data
	Union u1 = tilted_2_condition_1(g1, g2);
	Union u2 = tilted_2_condition_2(g1, g2);
	Union u3 = tilted_2_condition_3(g1, g2);
	//union
	Union uf = u1;
	uf = intersection(uf, u2);
	uf = intersection(uf, u3);
	uf = intersection(uf, Interval(1 / sqrt(1 - g1), inf));
	//trim
	union_trim_empty(uf);
	union_trim_fusion(uf);
	//data
	if(uf.m_ni == 0) return vec4(1, 0, 0, 1);
	if(uf.m_ni == 1 && uf.m_intervals[0].m_max == inf) return vec4(0, 0, 1, 1);
	if(uf.m_ni == 1 && uf.m_intervals[0].m_max != inf) return vec4(1, 0.5, 0, 1);
	return vec4(1, 0, 1, 1);
}

bool region(float g1, float g2)
{
	return abs(g1 - g2) < 1 && g1 + g2 > 1;
}
bool stability_vertical(float g1, float g2, float wp)
{
	//data
	const float e = 1 / g1 / g2;
	const float b = (g1 + g2) / g1 / g2;
	const float d = (g1 + g2 - 2) / g1 / g2;
	const float c = (g1 * g2 - g1 - g2 + 1) / g1 / g2;
	const float a = (2 * g1 * g2 - g1 - g2 + 1) / g1 / g2;
	//return
	const float B = a * wp * wp - b;
	const float C = c * wp * wp * wp * wp + d * wp * wp + e;
	return B > 0 && C > 0 && B * B - 4 * C > 0;
}
bool stability_tilted_1(float g1, float g2, float wp)
{
	//data
	const float c = (g1 - g2) * (1 - g2) / g1;
	const float a = 2 - g2 * (1 + g1 - g2) / g1;
	const float d = (g1 - g2) * (2 * g2 - 3) / g1 / g2 / (1 - g2);
	const float e = 3 * (g1 - g2) / g1 / g2 / (1 - g2) / (1 - g2);
	const float b = (1 - 2 * g1 - g2 * (1 + g1 - g2)) / g1 / g2 / (1 - g2);
	//data
	const float B = a * wp * wp + b / wp / wp;
	const float C = c * wp * wp * wp * wp + d + e / wp / wp / wp / wp;
	//return
	return B > 0 && C > 0 && B * B - 4 * C > 0;
}
bool stability_tilted_2(float g1, float g2, float wp)
{
	//data
	const float c = (g2 - g1) * (1 - g1) / g2;
	const float a = 2 - g1 * (1 + g2 - g1) / g2;
	const float d = (g2 - g1) * (2 * g1 - 3) / g2 / g1 / (1 - g1);
	const float e = 3 * (g2 - g1) / g2 / g1 / (1 - g1) / (1 - g1);
	const float b = (1 - 2 * g2 - g1 * (1 + g2 - g1)) / g2 / g1 / (1 - g1);
	//data
	const float B = a * wp * wp + b / wp / wp;
	const float C = c * wp * wp * wp * wp + d + e / wp / wp / wp / wp;
	//return
	return B > 0 && C > 0 && B * B - 4 * C > 0;
}
vec4 stability(float g1, float g2)
{
	//data
	const vec4 color_stable = vec4(0, 0, 1, 1);
	const vec4 color_unstable = vec4(1, 0, 0, 1);
	const vec4 color_impossible = vec4(0.5, 0.5, 0.5, 1);
	//check
	if(!region(g1, g2)) return color_impossible;
	if(mode == 1 && g2 > 1) return color_impossible;
	if(mode == 2 && g1 > 1) return color_impossible;
	//stability
	if(full != 0)
	{
		return 
			mode == 0 ? vertical_full(g1, g2) : 
			mode == 1 ? tilted_1_full(g1, g2) : 
			mode == 2 ? tilted_2_full(g1, g2) : color_impossible;
	}
	else
	{
		if(mode == 0)
		{
			return stability_vertical(g1, g2, wp) ? color_stable : color_unstable;
		}
		if(mode == 1)
		{
			const float wp = 1 / sqrt(cos(bt) * (1 - g2));
			return stability_tilted_1(g1, g2, wp) ? color_stable : color_unstable;
		}
		if(mode == 2)
		{
			const float wp = 1 / sqrt(cos(bt) * (1 - g1));
			return stability_tilted_2(g1, g2, wp) ? color_stable : color_unstable;
		}
		return color_impossible;
	}
}

void main(void)
{
	//data
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	const float g1 = (2 * gl_FragCoord.x - w + m) / m;
	const float g2 = (2 * gl_FragCoord.y - h + m) / m;
	//fragment
	fragment_color = stability(g1, g2);
}