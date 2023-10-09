#version 460 core

in vec3 vertex_color;
in vec2 vertex_texture;
out vec4 fragment_color;

uniform sampler2D fragment_sampler;

void main(void)
{
	fragment_color = texture2D(fragment_sampler, vertex_texture);
}