//canvas
#include "inc/Scene/Click.hpp"

namespace canvas
{
	//constructors
	Click::Click(void) : m_zoom(1.0f), m_shift{0.0f, 0.0f, 0.0f}, m_rotation{1.0f, 0.0f, 0.0f, 0.0f}, m_position{0, 0}
	{
		return;
	}

	//destructor
	Click::~Click(void)
	{
		return;
	}

	//data
	float Click::zoom(float zoom)
	{
		return m_zoom = zoom;
	}
	float Click::zoom(void) const
	{
		return m_zoom;
	}

	vec3 Click::shift(vec3 shift)
	{
		return m_shift = shift;
	}
	vec3 Click::shift(void) const
	{
		return m_shift;
	}

	quat Click::rotation(void) const
	{
		return m_rotation;
	}
	quat Click::rotation(quat rotation)
	{
		return m_rotation = rotation;
	}

	unsigned Click::position(unsigned index) const
	{
		return m_position[index];
	}
	unsigned Click::position(unsigned index, unsigned position)
	{
		return m_position[index] = position;
	}
}