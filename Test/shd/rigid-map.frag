#version 460 core

uniform uint full;
uniform uint mode;
uniform uint width;
uniform uint height;

uniform float wp;
uniform float wp_min;
uniform float wp_max;

out vec4 fragment_color;

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
vec4 stability(float g1, float g2)
{
	//data
	const vec4 colors[4] = {
		vec4(1, 0, 0, 1), vec4(0, 0, 1, 1), vec4(1, 0.5, 0, 1), vec4(1, 0, 1, 1)
	};
	//check
	if(!region(g1, g2)) return vec4(0.5, 0.5, 0.5, 0.5);
	//stability
	if(full != 0)
	{
		//data
		int counter = 0;
		const int nw = 100;
		bool v1 = false, v2;
		for(int i = 0; i <= nw; i++)
		{
			const float wp = wp_min + i * (wp_max - wp_min) / nw;
			v2 = stability_vertical(g1, g2, wp);
			if(v2 != v1)
			{
				v1 = v2;
				counter++;
			}
		}
		return colors[counter];
	}
	else
	{
		return stability_vertical(g1, g2, wp) ? colors[1] : colors[0];
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