#version 460 core

out vec4 vertex_color;
out vec2 vertex_texture_coordinates;

layout (location = 1) in vec4 color;
layout (location = 0) in vec2 position;
layout (location = 2) in vec2 texture_coordinates;

void main(void)
{
	vertex_color = color;
	vertex_texture_coordinates = texture_coordinates;
	gl_Position = vec4(position, -1, 1);
}