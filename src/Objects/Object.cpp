//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
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

		//affine
		mat4 Object::affine(void) const
		{
			return m_affine;
		}
		mat4 Object::affine(mat4 affine)
		{
			return m_affine = affine;
		}
		mat4 Object::apply_affine(mat4 affine)
		{
			return m_affine = affine * m_affine;
		}
	}
}