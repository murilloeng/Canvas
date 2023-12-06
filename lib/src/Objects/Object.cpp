//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Object::Object(void) : m_vbo_index{0, 0, 0}, m_ibo_index{0, 0, 0, 0, 0}
		{
			return;
		}

		//destructor
		Object::~Object(void)
		{
			return;
		}

		//model matrix
		mat4 Object::model_matrix(void) const
		{
			return m_model_matrix;
		}
		mat4 Object::model_matrix(mat4 model_matrix)
		{
			return m_model_matrix = model_matrix;
		}
		mat4 Object::apply_matrix(mat4 affine, bool left)
		{
			return m_model_matrix = left ? affine * m_model_matrix : m_model_matrix * affine;
		}

		void Object::scale(float s)
		{
			m_model_matrix = mat4::scaling(s) * m_model_matrix;
		}
		void Object::scale(const vec3& s, bool left)
		{
			const mat4 A = mat4::scaling(s);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::shift(const vec3& x , bool left)
		{
			const mat4 A = mat4::shifting(x);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const vec3& t, bool left)
		{
			const mat4 A = mat4::rotation(t);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const quat& q, bool left)
		{
			const mat4 A = mat4::rotation(q);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const vec3& x, const vec3& t, bool left)
		{
			const mat4 A = mat4::rotation(x, t);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const vec3& x, const quat& q, bool left)
		{
			const mat4 A = mat4::rotation(x, q);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}

		//buffers
		void Object::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			//data
			const unsigned ibo_offset[] = {1, 2, 3, 3, 3, 3};
			//buffers
			for(unsigned i = 0; i < 3; i++)
			{
				m_vbo_index[i] = vbo_counter[i];
				vbo_counter[i] += vbo_size(i);
			}
			for(unsigned i = 0; i < 6; i++)
			{
				m_ibo_index[i] = ibo_counter[i];
				ibo_counter[i] += ibo_offset[i] * ibo_size(i);
			}
		}

		//static
		Scene* Object::m_scene = nullptr;
	}
}