#version 460 core

out vec4 fragment_color;
in vec2 vertex_texture_coordinates;

layout(binding = 0) uniform sampler2D texture_unit;

void main(void)
{
	fragment_color = texture(texture_unit, vertex_texture_coordinates);
}