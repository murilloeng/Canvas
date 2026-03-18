//std
#include <cstring>

//canvas
#include "Canvas/Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Object::Object(void)
		{
			return;
		}

		//destructor
		Object::~Object(void)
		{
			return;
		}

		//data
		Scene* Object::scene(void) const
		{
			return m_scene;
		}

		//draw
		void Object::setup(void)
		{
			return;
		}
		void Object::draw(void) const
		{
			return;
		}

		//update
		void Object::update_on_motion(void) const
		{
			return;
		}
		void Object::update_bounding_box(cameras::BoundingBox&) const
		{
			return;
		}
	}
}