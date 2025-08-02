//canvas
#include "Canvas/Canvas/inc/Animations/Objects/Object.hpp"

namespace canvas
{
	namespace animations
	{
		namespace objects
		{
			//constructor
			Object::Object(canvas::objects::Object* object) : m_object{object}
			{
				return;
			}
			
			//destructor
			Object::~Object(void)
			{
				return;
			}
		}
	}
}