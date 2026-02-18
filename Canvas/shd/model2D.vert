#version 460 core

out vec4 vertex_color;

layout(location = 1) in vec4 color;
layout(location = 0) in vec2 position;

layout(std140, binding = 1) uniform camera { float width, height; };

void main(void)
{
	vertex_color = color;
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	// gl_Position = vec4(position, -1, 1);
	gl_Position = vec4(vec2(m / w, m / h) * position, -1, 1);
}