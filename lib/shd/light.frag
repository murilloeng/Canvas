#version 460 core

in vec4 geometry_color;
in vec3 geometry_normal;
out vec4 fragment_color;

void main(void)
{
	fragment_color = geometry_color;
}