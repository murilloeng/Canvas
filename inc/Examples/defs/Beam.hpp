#pragma once

//canvas
#include "inc/Objects/Group.hpp"

namespace examples
{
	class Beam : public canvas::objects::Group
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

		//type
		canvas::objects::type type(void) const override;

	private:
		//update
		void update_objects(void);

		//data
		float m_length;
		float m_height;
	};
}