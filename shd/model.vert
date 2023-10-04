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
	vec3 xc = (box_min + box_max) / 2;
	vec3 xs = (box_max - box_min) / 2;
	vec3 xp = (position - xc) / max(xs[0], max(xs[1], xs[2]));
	gl_Position = vec4(xp.xy, -xp.z, 1);
}