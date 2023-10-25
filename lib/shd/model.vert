#version 460 core

out vec4 vertex_color;

layout (location = 1) in vec4 color;
layout (location = 0) in vec3 position;

uniform uvec2 screen;
uniform float camera_far = 2.0;
uniform float camera_near = 1.0;
uniform bool camera_ortho = true;
uniform vec3 camera_position = vec3(0, 0, 0);
uniform vec4 camera_rotation = vec4(1, 0, 0, 0);

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

vec4 apply_camera(vec3 xw)
{
	//data
	vec4 xs;
	uint w = screen[0];
	uint h = screen[1];
	float m = min(w, h);
	float z2 = camera_far;
	float z1 = camera_near;
	float A = (z1 + z2) / (z2 - z1);
	float B = -2 * z1 * z2 / (z2 - z1);
	//affine
	xs.w = camera_ortho ? 1 : xw.z;
	xs.x = camera_ortho ? m / w * xw.x / (z2 - z1) : z1 * m / w * xw.x;
	xs.y = camera_ortho ? m / h * xw.y / (z2 - z1) : z1 * m / h * xw.y;
	xs.z = camera_ortho ? 2 * (xw.z - z1) / (z2 - z1) - 1 : A * xw.z + B;
	return xs;
}

void main(void)
{
	vertex_color = color;
	gl_Position = apply_camera(position);
}