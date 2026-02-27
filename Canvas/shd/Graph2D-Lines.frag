#version 460 core

in float vertex_length;

out vec4 fragment_color;

layout(std140, binding = 2) uniform Lines
{
	vec4 lines_color;
	uint lines_width;
	uint lines_enabled;
	uint lines_dash_size;
	uint lines_dash_type;
};

bool fragment_check_1(float p)
{
	return true;
}
bool fragment_check_2(float p)
{
	return p < 0.5;
}
bool fragment_check_3(float p)
{
	return p < 0.5 || p > 0.7 && p < 0.8;
}
bool fragment_check_4(float p)
{
	return p < 0.5 || p > 0.6 && p < 0.7 || p > 0.8 && p < 0.9;
}

bool fragment_check(float p)
{
	return 
		lines_dash_type == 1 ? fragment_check_1(p) : 
		lines_dash_type == 2 ? fragment_check_2(p) : 
		lines_dash_type == 3 ? fragment_check_3(p) : 
		lines_dash_type == 4 ? fragment_check_4(p) : false;
}

void main(void)
{
	//data
	const float p = mod(vertex_length, lines_dash_size) / lines_dash_size;
	//discard
	if(!fragment_check(p)) discard;
	//fragment
	fragment_color = lines_color;
}