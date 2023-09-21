//canvas
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		//destructor
		Object::Object(void) : m_vbo_index(0), m_ibo_index{0, 0, 0}
		{
			return;
		}

		Object::~Object(void)
		{
			return;
		}
	}
}