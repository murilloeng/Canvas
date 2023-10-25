#version 460 core

in vec4 vertex_color[];
out vec4 geometry_color;

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main(void)
{
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