//std
#include <cstring>

//canvas
#include "Canvas/inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Object::Object(void) : m_visible{true}
		{
			return;
		}

		//destructor
		Object::~Object(void)
		{
			return;
		}

		//data
		void Object::show(void)
		{
			m_visible = true;
		}
		void Object::hide(void)
		{
			m_visible = false;
		}
		bool Object::visible(void) const
		{
			return m_visible;
		}
		bool Object::visible(bool visible)
		{
			return m_visible = visible;
		}

		Scene* Object::scene(void) const
		{
			return m_scene;
		}

		//draw
		void Object::draw(void)
		{
			return;
		}
		void Object::setup(void)
		{
			return;
		}
		void Object::update(void)
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