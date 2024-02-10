#version 460 core

uniform mat4 view;
uniform mat4 projection;

out vec2 vertex_texture_coordinates;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coordinates;

void main(void)
{
	vertex_texture_coordinates = texture_coordinates;
	gl_Position = projection * view * vec4(position, 1);
}