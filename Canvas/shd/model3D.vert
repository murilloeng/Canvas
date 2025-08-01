#version 460 core

out vec4 vertex_color;

layout (location = 1) in vec4 color;
layout (location = 0) in vec3 position;

layout (std140, binding = 0) uniform camera { mat4 view, projection; };

void main(void)
{
	vertex_color = color;
	gl_Position = projection * view * vec4(position, 1);
}