#version 460 core

out vec4 vertex_color;

layout (location = 1) in vec4 color;
layout (location = 0) in vec3 position;

uniform uvec2 screen;
uniform bool camera_ortho = true;
uniform float camera_fov = 0.78539816339;
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

void main(void)
{
	//color
	vertex_color = color;
	//camera
	uint w = screen[0];
	uint h = screen[1];
	float m = min(w, h);
	float z1 = 1 / tan(camera_fov / 2);
	//affine
	float z2 = 8 * z1;
	float A = (z1 + z2) / (z2 - z1);
	float B = -2 * z1 * z2 / (z2 - z1);
	//position
	if(camera_ortho)
	{
		z2 = 256 * z1;
		gl_Position.w = 1;
		gl_Position.x = m / w * position.x / (z2 - z1);
		gl_Position.y = m / h * position.y / (z2 - z1);
		gl_Position.z = 2 * (position.z - z1) / (z2 - z1) - 1;
	}
	else
	{
		gl_Position = vec4(z1 * m / w * position.x, z1 * m / h * position.y, A * position.z + B, position.z);
	}
}