//std
#include <cstring>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Math/quat.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/Object.hpp"
#include "Canvas/inc/Vertices/Text2D.hpp"
#include "Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/inc/Vertices/Model2D.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Vertices/Image2D.hpp"
#include "Canvas/inc/Vertices/Image3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Object::Object(void) : m_has_model_matrix(false)
		{
			memset(m_vbo_size, 0, sizeof(m_vbo_size));
			memset(m_ibo_size, 0, sizeof(m_ibo_size));
			memset(m_vbo_index, 0, sizeof(m_vbo_index));
			memset(m_ibo_index, 0, sizeof(m_ibo_index));
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

		mat4 Object::model_matrix(void) const
		{
			return m_model_matrix;
		}
		mat4 Object::model_matrix(mat4 model_matrix)
		{
			m_has_model_matrix = true;
			return m_model_matrix = model_matrix;
		}
		mat4 Object::apply_matrix(mat4 affine, bool left)
		{
			m_has_model_matrix = true;
			return m_model_matrix = left ? affine * m_model_matrix : m_model_matrix * affine;
		}

		const uint32_t* Object::ibo_index(void) const
		{
			return m_ibo_index;
		}
		const uint32_t* Object::vbo_index(void) const
		{
			return m_vbo_index;
		}

		//buffers
		uint32_t* Object::ibo_data(uint32_t index) const
		{
			return m_scene->ibo(index).data() + m_ibo_index[index];
		}
		vertices::Text2D* Object::vbo_data_text_2D(void) const
		{
			return m_scene->vbo_data_text_2D() + m_vbo_index[5];
		}
		vertices::Text3D* Object::vbo_data_text_3D(void) const
		{
			return m_scene->vbo_data_text_3D() + m_vbo_index[2];
		}
		vertices::Model2D* Object::vbo_data_model_2D(void) const
		{
			return m_scene->vbo_data_model_2D() + m_vbo_index[3];
		}
		vertices::Model3D* Object::vbo_data_model_3D(void) const
		{
			return m_scene->vbo_data_model_3D() + m_vbo_index[0];
		}
		vertices::Image2D* Object::vbo_data_image_2D(void) const
		{
			return m_scene->vbo_data_image_2D() + m_vbo_index[4];
		}
		vertices::Image3D* Object::vbo_data_image_3D(void) const
		{
			return m_scene->vbo_data_image_3D() + m_vbo_index[1];
		}

		//affine
		void Object::scale(float s)
		{
			m_has_model_matrix = true;
			m_model_matrix = mat4::scaling(s) * m_model_matrix;
		}
		void Object::scale(const vec3& s, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::scaling(s);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::shift(const vec3& x , bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::shifting(x);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const vec3& t, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(t);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const quat& q, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(q);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const vec3& x, const vec3& t, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(x, t);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}
		void Object::rotate(const vec3& x, const quat& q, bool left)
		{
			m_has_model_matrix = true;
			const mat4 A = mat4::rotation(x, q);
			m_model_matrix = left ? A * m_model_matrix : m_model_matrix * A;
		}

		//buffers
		void Object::setup(void)
		{
			buffers_size();
			for(uint32_t i = 0; i < 6; i++)
			{
				m_vbo_index[i] = m_scene->m_vbos[i].m_size;
				m_scene->m_vbos[i].m_size += m_vbo_size[i];
			}
			for(uint32_t i = 0; i < 12; i++)
			{
				m_ibo_index[i] = m_scene->m_ibos[i].m_size;
				m_scene->m_ibos[i].m_size += m_ibo_size[i];
			}
		}
	}
}