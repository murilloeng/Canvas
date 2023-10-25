#version 460 core

in vec4 vertex_color[];

out vec4 geometry_color;
out vec3 geometry_normal;
out vec3 geometry_position;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform uvec2 screen;
uniform float camera_fov = 0.78539816339;
uniform vec3 camera_position = vec3(0, 0, 0);
uniform vec4 camera_rotation = vec4(1, 0, 0, 0);

void main(void)
{
	//camera
	uint w = screen[0];
	uint h = screen[1];
	float m = min(w, h);
	float z1 = 1 / tan(camera_fov / 2);
	//affine
	float z2 = 8 * z1;
	float A = (z1 + z2) / (z2 - z1);
	float B = -2 * z1 * z2 / (z2 - z1);
	//normal
	vec3 x0 = gl_in[0].gl_Position.xyz;
	vec3 x1 = gl_in[1].gl_Position.xyz;
	vec3 x2 = gl_in[2].gl_Position.xyz;
	geometry_normal = normalize(cross(x1 - x0, x2 - x0));
	//vertex 1
	geometry_color = vertex_color[0];
	geometry_position = gl_in[0].gl_Position.xyz;
	gl_Position = vec4(z1 * m / w * x0.x, z1 * m / h * x0.y, A * x0.z + B, x0.z);
	EmitVertex();
	//vertex 2
	geometry_color = vertex_color[1];
	geometry_position = gl_in[1].gl_Position.xyz;
	gl_Position = vec4(z1 * m / w * x1.x, z1 * m / h * x1.y, A * x1.z + B, x1.z);
	EmitVertex();
	//vertex 3
	geometry_color = vertex_color[2];
	geometry_position = gl_in[2].gl_Position.xyz;
	gl_Position = vec4(z1 * m / w * x2.x, z1 * m / h * x2.y, A * x2.z + B, x2.z);
	EmitVertex();
	//triangle
	EndPrimitive();
}