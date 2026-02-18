#version 460 core

out vec4 vertex_color;
out vec2 vertex_texture_coordinates;

layout(location = 1) in vec4 color;
layout(location = 0) in vec2 position;
layout(location = 2) in vec2 texture_coordinates;

layout(std140, binding = 1) uniform camera { float width, height; };

void main(void)
{
	//data
	vertex_color = color;
	vertex_texture_coordinates = texture_coordinates;
	//position
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	gl_Position = vec4(vec2(m / w, m / h) * position, -1, 1);
}