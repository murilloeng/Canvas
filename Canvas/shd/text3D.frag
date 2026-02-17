#version 460 core

out vec4 fragment_color;

in vec4 vertex_color;
in vec2 vertex_texture_coordinates;

layout(binding = 1) uniform sampler2D texture_unit;

void main(void)
{
	//data
	float v = texture(texture_unit, vertex_texture_coordinates).r;
	//fragment
	if(v == 0) discard;
	fragment_color = v * vertex_color;
}