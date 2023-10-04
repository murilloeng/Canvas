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

		//type
		canvas::objects::type type(void) const override;

	private:
		//update
		void update_objects(void);

		//data
		float m_size;
	};
}