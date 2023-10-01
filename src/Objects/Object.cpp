//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Object::Object(void) : m_dot(true), m_draw(true), m_fill(true), m_vbo_index(0), m_ibo_index{0, 0, 0}
		{
			return;
		}

		//destructor
		Object::~Object(void)
		{
			return;
		}

		//data
		bool Object::dot(bool dot)
		{
			return m_dot = dot;
		}
		bool Object::dot(void) const
		{
			return m_dot;
		}

		bool Object::draw(bool draw)
		{
			return m_draw = draw;
		}
		bool Object::draw(void) const
		{
			return m_draw;
		}

		bool Object::fill(bool fill)
		{
			return m_fill = fill;
		}
		bool Object::fill(void) const
		{
			return m_fill;
		}

		//name
		const char* Object::name(void) const
		{
			return Object::name(type());
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
		mat4 Object::apply_affine(mat4 affine, bool left)
		{
			return m_affine = left ? affine * m_affine : m_affine * affine;
		}
	}
}