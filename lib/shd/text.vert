#version 460 core

uniform mat4 camera_projection;

out vec4 vertex_color;
out vec2 vertex_texture_coordinates;

layout (location = 1) in vec4 color;
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texture_coordinates;

void main(void)
{
	vertex_color = color;
	vertex_texture_coordinates = texture_coordinates;
	gl_Position = camera_projection * vec4(position, 1);
}