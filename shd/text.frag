#version 460 core

out vec4 fragment_color;

in vec4 vertex_color_text;
in vec4 vertex_color_background;
in vec2 vertex_texture_coordinates;

uniform sampler2D fragment_sampler;

void main(void)
{
	float v = texture(fragment_sampler, vertex_texture_coordinates).r;
	fragment_color = v * vertex_color_text + (1 - v) * vertex_color_background;
}