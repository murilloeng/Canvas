//canvas
#include "inc/Objects/Type.hpp"
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

		//name
		const char* Object::name(void) const
		{
			return "";
			// return Object::name(type());
		}
		const char* Object::name(objects::type type)
		{
			switch(type)
			{
			case type::line:
				return "Line";
			case type::point:
				return "Point";
			case type::circle:
				return "Circle";
			case type::triangle:
				return "Triangle";
			default:
				return "Error";
			}
		}
	}
}