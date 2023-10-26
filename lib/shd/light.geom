#version 460 core

in vec4 vertex_color[];

out vec4 geometry_color;
out vec3 geometry_normal;
out vec3 geometry_position;

uniform uvec2 screen;
uniform bool camera_mode;
uniform float camera_far;
uniform float camera_near;
uniform vec3 camera_position;
uniform vec4 camera_rotation;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

vec4 conjugate(vec4 q)
{
	return vec4(q[0], -q[1], -q[2], -q[3]);
}
vec3 rotate(vec4 q, vec3 v)
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

vec4 camera_orthogonal(vec3 xw)
{
	//data
	vec4 xs;
	uint w = screen[0];
	uint h = screen[1];
	float m = min(w, h);
	float z2 = camera_far;
	float z1 = camera_near;
	float dz = (z2 - z1) / 2;
	float zm = (z1 + z2) / 2;
	//camera
	xw = xw - camera_position;
	xw = rotate(conjugate(camera_rotation), xw);
	//position
	xs.w = 1.0;
	xs.z = (xw.z - zm) / dz;
	xs.x = m / w * xw.x / dz;
	xs.y = m / h * xw.y / dz;
	//return
	return xs;
}
vec4 camera_perspective(vec3 xw)
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
	xs.w = xw.z;
	xs.z = A * xw.z + B;
	xs.x = z1 * m / w * xw.x;
	xs.y = z1 * m / h * xw.y;
	//return
	return xs;
}

void main(void)
{
	//normal
	vec3 x0 = gl_in[0].gl_Position.xyz;
	vec3 x1 = gl_in[1].gl_Position.xyz;
	vec3 x2 = gl_in[2].gl_Position.xyz;
	geometry_normal = normalize(cross(x1 - x0, x2 - x0));
	//vertex 1
	geometry_color = vertex_color[0];
	geometry_position = gl_in[0].gl_Position.xyz;
	gl_Position = camera_mode ? camera_orthogonal(x0) : camera_perspective(x0);
	EmitVertex();
	//vertex 2
	geometry_color = vertex_color[1];
	geometry_position = gl_in[1].gl_Position.xyz;
	gl_Position = camera_mode ? camera_orthogonal(x1) : camera_perspective(x1);
	EmitVertex();
	//vertex 3
	geometry_color = vertex_color[2];
	geometry_position = gl_in[2].gl_Position.xyz;
	gl_Position = camera_mode ? camera_orthogonal(x2) : camera_perspective(x2);
	EmitVertex();
	//triangle
	EndPrimitive();
}