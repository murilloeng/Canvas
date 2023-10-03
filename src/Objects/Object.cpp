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
		Object::Object(void) : m_dot(true), m_fill(true), m_stroke(true), m_vbo_index(0), m_ibo_index{0, 0, 0}
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

		bool Object::fill(bool fill)
		{
			return m_fill = fill;
		}
		bool Object::fill(void) const
		{
			return m_fill;
		}

		bool Object::stroke(void) const
		{
			return m_stroke;
		}
		bool Object::stroke(bool stroke)
		{
			return m_stroke = stroke;
		}

		void Object::dot_color(const Color& dot_color)
		{
			for(Color& color : m_dot_colors)
			{
				color = dot_color;
			}
		}
		void Object::dot_color(const Color& dot_color, unsigned index)
		{
			m_dot_colors[index] = dot_color;
		}

		void Object::fill_color(const Color& fill_color)
		{
			for(Color& color : m_fill_colors)
			{
				color = fill_color;
			}
		}
		void Object::fill_color(const Color& fill_color, unsigned index)
		{
			m_fill_colors[index] = fill_color;
		}

		void Object::stroke_color(const Color& stroke_color)
		{
			for(Color& color : m_stroke_colors)
			{
				color = stroke_color;
			}
			
		}
		void Object::stroke_color(const Color& stroke_color, unsigned index)
		{
			m_stroke_colors[index] = stroke_color;
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
			case type::arc:
				return "Arc";
			case type::cube:
				return "Cube";
			case type::line:
				return "Line";
			case type::quad:
				return "Quad";
			case type::point:
				return "Point";
			case type::circle:
				return "Circle";
			case type::triangle:
				return "Triangle";
			case type::sphere:
				return "Sphere";
			case type::grid_2D:
				return "Grid 2D";
			case type::grid_3D:
				return "Grid 3D";
			case type::cylinder:
				return "Cylinder";
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

		void Object::scale(float s)
		{
			m_affine = mat4::scaling(s) * m_affine;
		}
		void Object::scale(const vec3& s, bool left)
		{
			const mat4 A = mat4::scaling(s);
			m_affine = left ? A * m_affine : m_affine * A;
		}
		void Object::shift(const vec3& x , bool left)
		{
			const mat4 A = mat4::shifting(x);
			m_affine = left ? A * m_affine : m_affine * A;
		}
		void Object::rotate(const vec3& t, bool left)
		{
			const mat4 A = mat4::rotation(t);
			m_affine = left ? A * m_affine : m_affine * A;
		}
		void Object::rotate(const quat& q, bool left)
		{
			const mat4 A = mat4::rotation(q);
			m_affine = left ? A * m_affine : m_affine * A;
		}
		void Object::rotate(const vec3& x, const vec3& t, bool left)
		{
			const mat4 A = mat4::rotation(x, t);
			m_affine = left ? A * m_affine : m_affine * A;
		}
		void Object::rotate(const vec3& x, const quat& q, bool left)
		{
			const mat4 A = mat4::rotation(x, q);
			m_affine = left ? A * m_affine : m_affine * A;
		}
	}
}