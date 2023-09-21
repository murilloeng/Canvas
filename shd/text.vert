#version 460 core

out vec3 vertex_color;
out vec2 vertex_texture;

layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texture;
layout (location = 0) in vec3 position;

void main(void)
{
	vertex_color = color;
	vertex_texture = texture;
	gl_Position = vec4(position, 1);
}