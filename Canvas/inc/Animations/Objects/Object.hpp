#pragma once

//canvas
#include "Canvas/Canvas/inc/Objects/Object.hpp"

#include "Canvas/Canvas/inc/Animations/Animation.hpp"

namespace canvas
{
	namespace animations
	{
		namespace objects
		{
			class Object : public Animation
			{
			public:
				//constructor
				Object(canvas::objects::Object*);

				//destructor
				~Object(void);

			private:
				//data
				canvas::objects::Object* m_object;
			};
		}
	}
}