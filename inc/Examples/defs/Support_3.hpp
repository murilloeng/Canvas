#pragma once

//canvas
#include "inc/Objects/Group.hpp"

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
		float size(unsigned) const;
		float size(unsigned, float);

		//type
		canvas::objects::type type(void) const override;

	private:
		//update
		void update_objects(void);

		//data
		float m_size[2];
	};
}