#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"

namespace canvas
{
	enum class key : unsigned
	{
		left, right, down, up
	};
	enum class button : unsigned
	{
		none, left, middle, right
	};
	enum class modifier : unsigned
	{
		alt, ctrl, shift
	};
}

namespace canvas
{
	class Click
	{
	public:
		//constructors
		Click(void);

		//destructor
		~Click(void);

		//data
		vec3 shift(vec3);
		vec3 shift(void) const;

		quat rotation(quat);
		quat rotation(void) const;

		int position(unsigned, int);
		int position(unsigned) const;

		unsigned modifiers(unsigned);
		unsigned modifiers(void) const;

		canvas::button button(void) const;
		canvas::button button(canvas::button);

		//rotation
		static vec3 arcball(float, float);

	protected:
		vec3 m_shift;
		quat m_rotation;
		int m_position[2];
		unsigned m_modifiers;
		canvas::button m_button;
	};
}