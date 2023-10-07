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

		Color Object::color_dot(void) const
		{
			return m_color_dot;
		}
		Color Object::color_dot(const Color& color_dot)
		{
			return m_color_dot = color_dot;
		}

		Color Object::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Object::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Object::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Object::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
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
			case type::path:
				return "Path";
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

		//buffers
		void Object::buffers_index(unsigned& vbo_counter, unsigned ibo_counter[])
		{
			m_vbo_index = vbo_counter;
			vbo_counter += vbo_size();
			for(unsigned i = 0; i < 3; i++)
			{
				m_ibo_index[i] = ibo_counter[i];
				ibo_counter[i] += (i + 1) * ibo_size(i);
			}
		}
	}
}