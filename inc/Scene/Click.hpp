#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"

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

		unsigned position(unsigned) const;
		unsigned position(unsigned, unsigned);

	private:
		float m_zoom;
		vec3 m_shift;
		quat m_rotation;
		unsigned m_position[2];
	};
}