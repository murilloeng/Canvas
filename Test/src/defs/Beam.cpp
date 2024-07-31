//std
#include <cmath>

//examples
#include "Canvas/Test/inc/defs/Beam.hpp"

namespace examples
{
	//constructors
	Beam::Beam(float length, float height) : m_length(length), m_height(height)
	{
		//color
		m_color_fill = canvas::Color(0, 0, 1);
		m_color_stroke = canvas::Color(0, 0, 0);
		//points
		m_tessellator.points().resize(2 * m_na);
		m_tessellator.loops().push_back(2 * m_na);
	}

	//destructor
	Beam::~Beam(void)
	{
		return;
	}

	//data
	float Beam::height(void) const
	{
		return m_height;
	}
	float Beam::height(float height)
	{
		return m_height = height;
	}

	float Beam::length(void) const
	{
		return m_length;
	}
	float Beam::length(float length)
	{
		return m_length = length;
	}

	//setup
	void Beam::setup(unsigned vbo_counter[], unsigned ibo_counter[])
	{
		//data
		const float L = m_length;
		const float H = m_height;
		//points
		for(unsigned i = 0; i < m_na; i++)
		{
			const float t = (float) M_PI * i / (m_na - 1);
			m_tessellator.point(i) = {-H / 2 * sinf(t), H / 2 * cosf(t)};
		}
		for(unsigned i = 0; i < m_na; i++)
		{
			const float t = (float) M_PI * i / (m_na - 1);
			m_tessellator.point(i + m_na) = {L + H / 2 * sinf(t), -H / 2 * cosf(t)};
		}
		//polygon
		Polygon::setup(vbo_counter, ibo_counter);
	}

	//static
	unsigned Beam::m_na = 20;
}