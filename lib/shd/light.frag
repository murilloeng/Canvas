#version 460 core

out vec4 fragment_color;

in vec4 geometry_color;
in vec3 geometry_normal;
in vec3 geometry_position;

uniform vec3 camera_position;
uniform float light_alpha = 32;
uniform bool light_ambient = false;
uniform bool light_diffuse = false;
uniform bool light_specular = false;
uniform vec3 light_position = vec3(0, 0, 0);
uniform vec4 light_color_ambient = vec4(0.1, 0.1, 0.1, 1.0);
uniform vec4 light_color_diffuse = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec4 light_color_specular = vec4(1.0, 1.0, 1.0, 1.0);

void apply_light_ambient(void)
{
	fragment_color.r += geometry_color.r * light_color_ambient.r;
	fragment_color.g += geometry_color.g * light_color_ambient.g;
	fragment_color.b += geometry_color.b * light_color_ambient.b;
}
void apply_diffuse_color(vec3 vl)
{
	fragment_color.r += dot(geometry_normal, vl) * geometry_color.r * light_color_diffuse.r;
	fragment_color.g += dot(geometry_normal, vl) * geometry_color.g * light_color_diffuse.g;
	fragment_color.b += dot(geometry_normal, vl) * geometry_color.b * light_color_diffuse.b;
}
void apply_specular_color(vec3 vc, vec3 vr)
{
	fragment_color.r += pow(dot(vc, vr), light_alpha) * geometry_color.r * light_color_specular.r;
	fragment_color.g += pow(dot(vc, vr), light_alpha) * geometry_color.g * light_color_specular.g;
	fragment_color.b += pow(dot(vc, vr), light_alpha) * geometry_color.b * light_color_specular.b;
}

void main(void)
{
	if(!light_ambient && !light_diffuse && !light_specular)
	{
		fragment_color = geometry_color;
	}
	else
	{
		//data
		vec3 vl = normalize(light_position - geometry_position);
		vec3 vc = normalize(camera_position - geometry_position);
		vec3 vr = -reflect(vl, geometry_normal);
		//color
		fragment_color = vec4(0, 0, 0, 1);
		if(light_ambient) apply_light_ambient();
		if(light_diffuse && dot(geometry_normal, vl) > 0) apply_diffuse_color(vl);
		if(light_specular && dot(geometry_normal, vl) > 0 && dot(vc, vr) > 0) apply_specular_color(vc, vr);
	}
}