#version 460 core

out vec2 vertex_texture;

layout (location = 1) in vec2 texture;
layout (location = 0) in vec3 position;

uniform uvec2 screen = uvec2(700, 700);

uniform vec3 box_min = vec3(-1, -1, -1);
uniform vec3 box_max = vec3(+1, +1, +1);

uniform float zoom = 1;
uniform vec3 shift = vec3(0, 0, 0);
uniform vec4 rotation = vec4(1, 0, 0, 0);

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
	//screen
	uint w = screen[0];
	uint h = screen[1];
	float m = min(w, h);
	//camera
	float z = zoom;
	vec3 xa = shift;
	vec4 qr = rotation;
	//outputs
	vertex_texture = texture;
	//position
	vec3 xc = (box_min + box_max) / 2;
	vec3 xs = (box_max - box_min) / 2;
	float s = max(xs[0], max(xs[1], xs[2]));
	vec3 xp = z / s * quat_rotation(qr, position - xc) + xa;
	gl_Position = vec4(vec2(m / w, m / h) * xp.xy, -1e-2 * xp.z, 1);
}