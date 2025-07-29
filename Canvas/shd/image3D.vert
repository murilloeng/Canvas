#version 460 core

out vec2 vertex_texture_coordinates;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coordinates;

layout (std140, binding = 0) uniform camera { mat4 view, projection; };

void main(void)
{
	vertex_texture_coordinates = texture_coordinates;
	gl_Position = projection * view * vec4(position, 1);
}