#pragma once

//canvas
#include "inc/Objects/Group.hpp"

namespace examples
{
	class Support_1 : public canvas::objects::Group
	{
	public:
		//constructors
		Support_1(float);

		//destructor
		~Support_1(void);

		//data
		float size(float);
		float size(void) const;

	private:
		//update
		void update_objects(void);

		//data
		float m_size;
	};
}