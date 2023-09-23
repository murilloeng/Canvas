#version 460 core

uniform vec3 pan;
uniform vec4 quat;
uniform float zoom;

uniform vec3 box_min;
uniform vec3 box_max;

uniform uvec2 screen;

out vec4 vertex_color;

layout (location = 0) in vec4 color;
layout (location = 1) in vec3 position;

void main(void)
{
	vertex_color = color;
	gl_Position = vec4(position, 1);
}