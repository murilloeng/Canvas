#version 460 core

out vec4 fragment_color;

in vec4 geometry_color;
in vec3 geometry_normal;
in vec3 geometry_position;

struct Point
{
	vec3 m_color;
	vec3 m_position;
};
struct Ambient
{
	vec3 m_color;
};
struct Direction
{
	vec3 m_color;
	vec3 m_direction;
};

const int n_max = 200;
uniform uint n_points = 0;
uniform uint n_directions = 0;
uniform vec3 camera_position;

uniform Point points[n_max];
uniform Direction directions[n_max];
uniform Ambient ambient = Ambient(vec3(0, 0, 0));

void main(void)
{
	//data
	const vec3 vc = normalize(camera_position - geometry_position);
	//check
	if(n_points == 0 && n_directions == 0 && length(ambient.m_color) == 0)
	{
		fragment_color = geometry_color;
		return;
	}
	//alpha
	fragment_color.a = geometry_color.a;
	//ambient
	fragment_color.r = geometry_color.r * ambient.m_color.r;
	fragment_color.g = geometry_color.g * ambient.m_color.g;
	fragment_color.b = geometry_color.b * ambient.m_color.b;
	//direction
	for(uint i = 0; i < n_directions; i++)
	{
		const float dd = dot(geometry_normal, normalize(directions[i].m_direction));
		if(dd > 0)
		{
			fragment_color.r += dd * geometry_color.r * directions[i].m_color.r;
			fragment_color.g += dd * geometry_color.g * directions[i].m_color.g;
			fragment_color.b += dd * geometry_color.b * directions[i].m_color.b;
		}
	}
	//point
	for(uint i = 0; i < n_points; i++)
	{
		const float rp = length(points[i].m_position - geometry_position);
		const float dp = dot(geometry_normal, normalize(points[i].m_position - geometry_position));
		if(dp > 0)
		{
			fragment_color.r += dp * geometry_color.r * points[i].m_color.r / rp / rp;
			fragment_color.g += dp * geometry_color.g * points[i].m_color.g / rp / rp;
			fragment_color.b += dp * geometry_color.b * points[i].m_color.b / rp / rp;
		}
	}
}