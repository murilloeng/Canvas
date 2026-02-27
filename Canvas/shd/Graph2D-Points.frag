#version 460 core

out vec4 fragment_color;

layout(std140, binding = 2) uniform Points
{
	vec4 points_color;
	uint points_size;
	uint points_skip;
	uint points_type;
	uint points_enabled;
};

float triangle_sign(vec2 p1, vec2 p2, vec2 p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool point_in_triangle(vec2 p, vec2 a, vec2 b, vec2 c)
{
	float d1 = triangle_sign(p, a, b);
	float d2 = triangle_sign(p, b, c);
	float d3 = triangle_sign(p, c, a);
	bool sign_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool sign_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
	return !(sign_neg && sign_pos);
}

bool fragment_check_1(vec2 p)
{
	return abs(p.x) < 0.1 || abs(p.y) < 0.1;
}
bool fragment_check_2(vec2 p)
{
	const float s2 = sqrt(2);
	return abs(p.x + p.y) < 0.1 * s2 || abs(p.x - p.y) < 0.1 * s2;
}
bool fragment_check_3(vec2 p)
{
	return fragment_check_1(p) || fragment_check_2(p);
}
bool fragment_check_4(vec2 p)
{
	return p.x < -0.9 || p.x > 0.9 || p.y < -0.9 || p.y > 0.9;
}
bool fragment_check_5(vec2 p)
{
	return true;
}
bool fragment_check_6(vec2 p)
{
	const float r = length(p);
	return r > 0.9 && r < 1.0;
}
bool fragment_check_7(vec2 p)
{
	return length(p) < 1.0;
}
bool fragment_check_8(vec2 p)
{
	//data
	const vec2 a1 = 1.0 * vec2(cos(radians( 90)), sin(radians( 90)));
	const vec2 b1 = 1.0 * vec2(cos(radians(210)), sin(radians(210)));
	const vec2 c1 = 1.0 * vec2(cos(radians(330)), sin(radians(330)));
	const vec2 a2 = 0.8 * vec2(cos(radians( 90)), sin(radians( 90)));
	const vec2 b2 = 0.8 * vec2(cos(radians(210)), sin(radians(210)));
	const vec2 c2 = 0.8 * vec2(cos(radians(330)), sin(radians(330)));
	//return
	return point_in_triangle(p, a1, b1, c1) && !point_in_triangle(p, a2, b2, c2);
}
bool fragment_check_9(vec2 p)
{
	//data
	const vec2 a = vec2(cos(radians( 90)), sin(radians( 90)));
	const vec2 b = vec2(cos(radians(210)), sin(radians(210)));
	const vec2 c = vec2(cos(radians(330)), sin(radians(330)));
	//return
	return point_in_triangle(p, a, b, c);
}
bool fragment_check_10(vec2 p)
{
	//data
	const vec2 a1 = 1.0 * vec2(cos(radians( 30)), sin(radians( 30)));
	const vec2 b1 = 1.0 * vec2(cos(radians(150)), sin(radians(150)));
	const vec2 c1 = 1.0 * vec2(cos(radians(270)), sin(radians(270)));
	const vec2 a2 = 0.8 * vec2(cos(radians( 30)), sin(radians( 30)));
	const vec2 b2 = 0.8 * vec2(cos(radians(150)), sin(radians(150)));
	const vec2 c2 = 0.8 * vec2(cos(radians(270)), sin(radians(270)));
	//return
	return point_in_triangle(p, a1, b1, c1) && !point_in_triangle(p, a2, b2, c2);
}
bool fragment_check_11(vec2 p)
{
	//data
	const vec2 a = vec2(cos(radians( 30)), sin(radians( 30)));
	const vec2 b = vec2(cos(radians(150)), sin(radians(150)));
	const vec2 c = vec2(cos(radians(270)), sin(radians(270)));
	//return
	return point_in_triangle(p, a, b, c);
}
bool fragment_check_12(vec2 p)
{
	const vec2 a = vec2(0, 0);
	for(uint i = 0; i < 4; i++)
	{
		const float t1 = radians(90 * (i + 0));
		const float t2 = radians(90 * (i + 1));
		const vec2 b = vec2(cos(t1), sin(t1));
		const vec2 c = vec2(cos(t2), sin(t2));
		if(point_in_triangle(p, a, b, c) && !point_in_triangle(p, a, 0.8 * b, 0.8 * c)) return true;
	}
	return false;
}
bool fragment_check_13(vec2 p)
{
	const vec2 a = vec2(0, 0);
	for(uint i = 0; i < 4; i++)
	{
		const float t1 = radians(90 * (i + 0));
		const float t2 = radians(90 * (i + 1));
		const vec2 b = vec2(cos(t1), sin(t1));
		const vec2 c = vec2(cos(t2), sin(t2));
		if(point_in_triangle(p, a, b, c)) return true;
	}
	return false;
}
bool fragment_check_14(vec2 p)
{
	const vec2 a = vec2(0, 0);
	for(int i = 0; i < 5; i++)
	{
		const float t1 = radians(72 * (i + 0) - 90);
		const float t2 = radians(72 * (i + 1) - 90);
		const vec2 b = vec2(cos(t1), sin(t1));
		const vec2 c = vec2(cos(t2), sin(t2));
		if(point_in_triangle(p, a, b, c) && !point_in_triangle(p, a, 0.8 * b, 0.8 * c)) return true;
	}
	return false;
}
bool fragment_check_15(vec2 p)
{
	const vec2 a = vec2(0, 0);
	for(int i = 0; i < 5; i++)
	{
		const float t1 = radians(72 * (i + 0) - 90);
		const float t2 = radians(72 * (i + 1) - 90);
		const vec2 b = vec2(cos(t1), sin(t1));
		const vec2 c = vec2(cos(t2), sin(t2));
		if(point_in_triangle(p, a, b, c)) return true;
	}
	return false;
}

bool fragment_check(vec2 p)
{
	return 
		points_type ==  1 ? fragment_check_1(p) : 
		points_type ==  2 ? fragment_check_2(p) : 
		points_type ==  3 ? fragment_check_3(p) : 
		points_type ==  4 ? fragment_check_4(p) : 
		points_type ==  5 ? fragment_check_5(p) : 
		points_type ==  6 ? fragment_check_6(p) : 
		points_type ==  7 ? fragment_check_7(p) : 
		points_type ==  8 ? fragment_check_8(p) : 
		points_type ==  9 ? fragment_check_9(p) : 
		points_type == 10 ? fragment_check_10(p) : 
		points_type == 11 ? fragment_check_11(p) : 
		points_type == 12 ? fragment_check_12(p) : 
		points_type == 13 ? fragment_check_13(p) : 
		points_type == 14 ? fragment_check_14(p) : 
		points_type == 15 ? fragment_check_15(p) : false;
}

void main(void)
{
	//data
	const vec2 p = vec2(1, -1) * (2 * gl_PointCoord - 1);
	//discard
	if(!fragment_check(p)) discard;
	//fragment
	fragment_color = points_color;
	
}