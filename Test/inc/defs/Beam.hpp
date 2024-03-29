#pragma once

//canvas
#include "Canvas/inc/Objects/2D/Polygon.hpp"

namespace examples
{
	class Beam : public canvas::objects::Polygon
	{
	public:
		//constructors
		Beam(float, float);

		//destructor
		~Beam(void);

		//data
		float height(float);
		float height(void) const;

		float length(float);
		float length(void) const;

	protected:
		//setup
		void setup(unsigned[], unsigned[]) override;

		//data
		float m_length;
		float m_height;
		static unsigned m_na;
	};
}