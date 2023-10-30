//std
#include <cmath>

//canvas
#include "inc/Scene/Click.hpp"

namespace canvas
{
	//constructors
	Click::Click(void) : 
		m_screen{0, 0}, m_position{0.0f, 0.0f, 0.0f}, 
		m_rotation{1.0f, 0.0f, 0.0f, 0.0f}, m_modifiers(0), m_button(canvas::button::none)
	{
		return;
	}

	//destructor
	Click::~Click(void)
	{
		return;
	}

	//data
	vec3 Click::position(void) const
	{
		return m_position;
	}
	vec3 Click::position(vec3 position)
	{
		return m_position = position;
	}

	quat Click::rotation(void) const
	{
		return m_rotation;
	}
	quat Click::rotation(quat rotation)
	{
		return m_rotation = rotation;
	}

	int Click::screen(unsigned index) const
	{
		return m_screen[index];
	}
	int Click::screen(unsigned index, int screen)
	{
		return m_screen[index] = screen;
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