#version 460 core

out vec4 vertex_color;

uniform uvec2 screen = uvec2(700, 700);

uniform vec3 box_min = vec3(-1, -1, -1);
uniform vec3 box_max = vec3(+1, +1, +1);

uniform float zoom = 1;
uniform vec3 shift = vec3(0, 0, 0);
uniform vec4 rotation = vec4(1, 0, 0, 0);

layout (location = 0) in vec4 color;
layout (location = 1) in vec3 position;

vec3 quat_rotation(vec4 q, vec3 v)
{
	vec3 r;
	vec3 x = q.yzw;
	float s = q[0];
	float b = 2 * dot(x, v);
	float a = s * s - dot(x, x);
	r[0] = a * v[0] + b * x[0] + 2 * s * (x[1] * v[2] - x[2] * v[1]);
	r[1] = a * v[1] + b * x[1] + 2 * s * (x[2] * v[0] - x[0] * v[2]);
	r[2] = a * v[2] + b * x[2] + 2 * s * (x[0] * v[1] - x[1] * v[0]);
	return r;
}

void main(void)
{
	//color
	vertex_color = color;
	//screen
	uint w = screen[0];
	uint h = screen[1];
	//position
	vec3 xc = (box_min + box_max) / 2;
	vec3 xs = (box_max - box_min) / 2;
	float s = max(xs[0], max(xs[1], xs[2]));
	vec3 xp = zoom * quat_rotation(rotation, position - xc - shift) / s;
	gl_Position = vec4(vec2(w, h) * xp.xy / min(w, h), -xp.z, 1);
}