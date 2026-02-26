#version 460 core

out vec4 fragment_color;

layout(std430, binding = 0) buffer Curve
{
	vec4 color;
	uint count;
	uint thickness;
	vec2 positions[];
};

void main(void)
{
	fragment_color = color;
}