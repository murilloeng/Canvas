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
		vec3 pan(vec3);
		vec3 pan(void) const;

		quat rotation(quat);
		quat rotation(void) const;

		unsigned position(unsigned) const;
		unsigned position(unsigned, unsigned);

	private:
		vec3 m_pan;
		quat m_rotation;
		unsigned m_position[2];
	};
}