#version 460 core

in vec4 vertex_color;
in vec2 vertex_texture;
out vec4 fragment_color;

uniform sampler2D fragment_sampler;

void main(void)
{
	fragment_color = texture2D(fragment_sampler, vertex_texture).r * vertex_color;
}