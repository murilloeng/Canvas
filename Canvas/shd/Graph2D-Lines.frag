#version 460 core

out vec4 fragment_color;

layout(std140, binding = 2) uniform Lines
{
	vec4 lines_color;
	uint lines_width;
	uint lines_enabled;
	uint lines_dash_size;
	uint lines_dash_type;
};

void main(void)
{
	fragment_color = lines_color;
}