#version 460 core

out vec4 fragment_color;
in vec2 vertex_texture_coordinates;

layout(binding = 0) uniform sampler2D fragment_sampler;

void main(void)
{
	fragment_color = texture(fragment_sampler, vertex_texture_coordinates);
}