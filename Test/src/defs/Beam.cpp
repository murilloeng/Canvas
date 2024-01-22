//std
#include <cmath>

//examples
#include "inc/defs/Beam.hpp"

namespace examples
{
	//constructors
	Beam::Beam(float length, float height) : m_length(length), m_height(height)
	{
		m_points.resize(2 * m_na + 2);
		m_loops.push_back(2 * m_na + 2);
		m_color_fill = canvas::Color(0, 0, 1);
		m_color_stroke = canvas::Color(0, 0, 0);
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
		const float a = float(M_PI_2);
		for(unsigned i = 0; i <= m_na; i++)
		{
			const float t = a * i / m_na  + a;
			m_points[i] = {m_height / 2 * cosf(t), m_height / 2 * sinf(t)};
		}
		for(unsigned i = 0; i <= m_na; i++)
		{
			const float t = a * i / m_na  - a;
			m_points[i + m_na + 1] = {m_length + m_height / 2 * cosf(t), m_height / 2 * sinf(t)};
		}
		Polygon::setup(vbo_counter, ibo_counter);
	}

	//static
	unsigned Beam::m_na = 40;
}