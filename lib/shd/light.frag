#version 460 core

in vec4 geometry_color;
out vec4 fragment_color;

void main(void)
{
	fragment_color = geometry_color;
}