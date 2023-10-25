#version 460 core

in vec4 vertex_color[];
out vec4 geometry_color;
out vec3 geometry_normal;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main(void)
{
	vec3 x0 = gl_in[0].gl_Position.xyz;
	vec3 x1 = gl_in[1].gl_Position.xyz;
	vec3 x2 = gl_in[2].gl_Position.xyz;
	geometry_normal = normalize(cross(x1 - x0, x2 - x0));

	geometry_color = vertex_color[0];
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

	geometry_color = vertex_color[1];
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();

	geometry_color = vertex_color[2];
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}