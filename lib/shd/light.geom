#version 460 core

in vec4 vertex_color[];

out vec4 geometry_color;
out vec3 geometry_normal;
out vec3 geometry_position;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform uvec2 screen;
uniform float camera_far = 2.0;
uniform float camera_near = 1.0;
uniform bool camera_ortho = true;
uniform vec3 camera_position = vec3(0, 0, 0);
uniform vec4 camera_rotation = vec4(1, 0, 0, 0);

vec4 apply_camera(vec4 xw)
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
	//normal
	vec3 x0 = gl_in[0].gl_Position.xyz;
	vec3 x1 = gl_in[1].gl_Position.xyz;
	vec3 x2 = gl_in[2].gl_Position.xyz;
	geometry_normal = normalize(cross(x1 - x0, x2 - x0));
	//vertex 1
	geometry_color = vertex_color[0];
	geometry_position = gl_in[0].gl_Position.xyz;
	gl_Position = apply_camera(gl_in[0].gl_Position);
	EmitVertex();
	//vertex 2
	geometry_color = vertex_color[1];
	geometry_position = gl_in[1].gl_Position.xyz;
	gl_Position = apply_camera(gl_in[1].gl_Position);
	EmitVertex();
	//vertex 3
	geometry_color = vertex_color[2];
	geometry_position = gl_in[2].gl_Position.xyz;
	gl_Position = apply_camera(gl_in[2].gl_Position);
	EmitVertex();
	//triangle
	EndPrimitive();
}