//std
#include <cmath>

//canvas
#include "inc/Scene/Click.hpp"

namespace canvas
{
	//constructors
	Click::Click(void) : 
		m_shift{0.0f, 0.0f, 0.0f}, m_rotation{1.0f, 0.0f, 0.0f, 0.0f}, 
		m_position{0, 0}, m_modifiers(0), m_button(canvas::button::none)
	{
		return;
	}

	//destructor
	Click::~Click(void)
	{
		return;
	}

	//data
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

	int Click::position(unsigned index) const
	{
		return m_position[index];
	}
	int Click::position(unsigned index, int position)
	{
		return m_position[index] = position;
	}

	unsigned Click::modifiers(void) const
	{
		return m_modifiers;
	}
	unsigned Click::modifiers(unsigned modifiers)
	{
		return m_modifiers = modifiers;
	}

	canvas::button Click::button(void) const
	{
		return m_button;
	}
	canvas::button Click::button(canvas::button button)
	{
		return m_button = button;
	}

	//rotation
	vec3 Click::arcball(float x1, float x2)
	{
		const float r = sqrtf(x1 * x1 + x2 * x2);
		return vec3(x1 / fmaxf(r, 1), x2 / fmaxf(r, 1), sqrtf(1 - fminf(r * r, 1)));
	}
}