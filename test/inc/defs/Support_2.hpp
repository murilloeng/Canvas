#pragma once

//canvas
#include "inc/Objects/Group.hpp"

namespace examples
{
	class Support_2 : public canvas::objects::Group
	{
	public:
		//constructors
		Support_2(float);

		//destructor
		~Support_2(void);

		//data
		float size(float);
		float size(void) const;

	protected:
		//update
		void update_objects(void);

		//data
		float m_size;
	};
}