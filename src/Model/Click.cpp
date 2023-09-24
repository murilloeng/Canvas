//canvas
#include "inc/Models/Click.hpp"

namespace canvas
{
	//constructors
	Click::Click(void) : m_pan{0, 0, 0}, m_rotation{1, 0, 0, 0}, m_position{0, 0}
	{
		return;
	}

	//destructor
	Click::~Click(void)
	{
		return;
	}

	//data
	vec3 Click::pan(vec3 pan)
	{
		return m_pan = pan;
	}
	vec3 Click::pan(void) const
	{
		return m_pan;
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