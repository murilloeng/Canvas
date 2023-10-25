#version 460 core

float shininess = 32;

in vec4 geometry_color;
in vec3 geometry_normal;
in vec3 geometry_position;

out vec4 fragment_color;

struct Light
{
	vec3 m_position;
	bool m_has_ambient;
	bool m_has_diffuse;
	bool m_has_specular;
	vec3 m_color_ambient;
	vec3 m_color_diffuse;
	vec3 m_color_specular;
};

uniform Light light = Light(
	vec3(0.0, 0.0, 1.0), false, false, false,
	vec3(0.5, 0.5, 0.5), vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0)
);

void main(void)
{
	if(!light.m_has_ambient && !light.m_has_diffuse && !light.m_has_specular)
	{
		fragment_color = geometry_color;
	}
	else
	{
		//data
		fragment_color = vec4(0, 0, 0, 1);
		vec3 vpv = normalize(vec3(0, 0, 1) - geometry_position);
		vec3 vpl = normalize(light.m_position - geometry_position);
		vec3 vrn = -reflect(vpl, geometry_normal);
		//ambient
		if(light.m_has_ambient)
		{
			fragment_color.r += geometry_color.r * light.m_color_ambient.r;
			fragment_color.g += geometry_color.g * light.m_color_ambient.g;
			fragment_color.b += geometry_color.b * light.m_color_ambient.b;
		}
		//diffuse
		if(light.m_has_diffuse && dot(geometry_normal, vpl) > 0)
		{
			fragment_color.r += dot(geometry_normal, vpl) * geometry_color.r * light.m_color_diffuse.r;
			fragment_color.g += dot(geometry_normal, vpl) * geometry_color.g * light.m_color_diffuse.g;
			fragment_color.b += dot(geometry_normal, vpl) * geometry_color.b * light.m_color_diffuse.b;
		}
		//specular
		if(light.m_has_specular && dot(vpv, vrn) > 0)
		{
			float a = shininess;
			fragment_color.r += pow(dot(vpv, vrn), a) * geometry_color.r * light.m_color_specular.r;
			fragment_color.g += pow(dot(vpv, vrn), a) * geometry_color.g * light.m_color_specular.g;
			fragment_color.b += pow(dot(vpv, vrn), a) * geometry_color.b * light.m_color_specular.b;
		}
	}
}