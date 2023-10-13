#version 460 core

in vec2 vertex_texture;
out vec4 fragment_color;

uniform sampler2D fragment_sampler;

void main(void)
{
	fragment_color = texture(fragment_sampler, vertex_texture);
}