#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"

namespace canvas
{
	enum class button : unsigned
	{
		none,
		left,
		right,
		middle
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
		float zoom(float);
		float zoom(void) const;

		vec3 shift(vec3);
		vec3 shift(void) const;

		quat rotation(quat);
		quat rotation(void) const;

		int position(unsigned, int);
		int position(unsigned) const;

		canvas::button button(void) const;
		canvas::button button(canvas::button);

	private:
		float m_zoom;
		vec3 m_shift;
		quat m_rotation;
		int m_position[2];
		canvas::button m_button;
	};
}