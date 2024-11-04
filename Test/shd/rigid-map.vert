#version 460 core

uniform uint width;
uniform uint height;

out vec4 vertex_color;

layout (location = 1) in vec4 color;
layout (location = 0) in vec2 position;

void main(void)
{
	//data
	const float w = width;
	const float h = height;
	const float m = min(w, h);
	const float x1 = m / w * position.x;
	const float x2 = m / h * position.y;
	//return
	vertex_color = color;
	gl_Position = vec4(x1, x2, -1, 1);
}