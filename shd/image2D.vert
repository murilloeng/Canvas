#version 460 core

out vec2 vertex_texture_coordinates;

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texture_coordinates;

void main(void)
{
	vertex_texture_coordinates = texture_coordinates;
	gl_Position = vec4(position, -1, 1);
}