#pragma once

//canvas
#include "Canvas/inc/Objects/Group.hpp"

namespace examples
{
	class Support_3 : public canvas::objects::Group
	{
	public:
		//constructors
		Support_3(float, float);

		//destructor
		~Support_3(void);

		//data
		float size(uint32_t) const;
		float size(uint32_t, float);

	protected:
		//update
		void update_objects(void);

		//data
		float m_size[2];
	};
}