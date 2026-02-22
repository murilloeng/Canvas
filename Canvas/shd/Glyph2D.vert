#version 460 core

out vec4 vertex_color;
out vec2 vertex_texture_coordinates;

layout(location = 0) in vec4 color;
layout(location = 1) in vec2 positions[4];
layout(location = 5) in vec2 texture_coordinates[4];

layout(std140, binding = 1) uniform screen { float width, height; };

void main(void)
{
	//data
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	//vertex
	vertex_color = color;
	vertex_texture_coordinates = texture_coordinates[gl_VertexID];
	gl_Position = vec4(vec2(m / w, m / h) * positions[gl_VertexID], -1, 1);
}