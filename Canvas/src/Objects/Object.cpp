//std
#include <cstring>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/quat.hpp"

#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Objects/Object.hpp"

#include "Canvas/Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image2D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

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