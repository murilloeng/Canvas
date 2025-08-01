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
		Object::Object(void) : m_has_model_matrix(false), 
			m_vbo_size(6, 0), m_ibo_size(12, 0), m_vbo_index(6, 0), m_ibo_index(12, 0)
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
			return m_ibo_index.data();
		}
		const uint32_t* Object::vbo_index(void) const
		{
			return m_vbo_index.data();
		}

		//buffers
		uint32_t* Object::ibo_data(uint32_t index) const
		{
			return m_scene->m_ibos[index]->m_data + m_ibo_index[index];
		}
		vertices::Text2D* Object::vbo_data_text_2D(void) const
		{
			return (vertices::Text2D*) m_scene->m_vbos[5]->m_data + m_vbo_index[5];
		}
		vertices::Text3D* Object::vbo_data_text_3D(void) const
		{
			return (vertices::Text3D*) m_scene->m_vbos[2]->m_data + m_vbo_index[2];
		}
		vertices::Model2D* Object::vbo_data_model_2D(void) const
		{
			return (vertices::Model2D*) m_scene->m_vbos[3]->m_data + m_vbo_index[3];
		}
		vertices::Model3D* Object::vbo_data_model_3D(void) const
		{
			return (vertices::Model3D*) m_scene->m_vbos[0]->m_data + m_vbo_index[0];
		}
		vertices::Image2D* Object::vbo_data_image_2D(void) const
		{
			return (vertices::Image2D*) m_scene->m_vbos[4]->m_data + m_vbo_index[4];
		}
		vertices::Image3D* Object::vbo_data_image_3D(void) const
		{
			return (vertices::Image3D*) m_scene->m_vbos[1]->m_data + m_vbo_index[1];
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
			for(uint32_t i = 0; i < m_vbo_index.size(); i++)
			{
				m_vbo_index[i] = m_scene->m_vbos[i]->m_vertex_count;
				m_scene->m_vbos[i]->m_vertex_count += m_vbo_size[i];
			}
			for(uint32_t i = 0; i < m_ibo_size.size(); i++)
			{
				m_ibo_index[i] = m_scene->m_ibos[i]->m_vertex_count;
				m_scene->m_ibos[i]->m_vertex_count += m_ibo_size[i];
			}
		}

		//update
		void Object::update_on_motion(void) const
		{
			return;
		}

		//model matrix
		void Object::apply_model_matrix(void) const
		{
			//data
			if(!m_has_model_matrix) return;
			vertices::Text3D* text_3D_ptr = vbo_data_text_3D();
			vertices::Model3D* model_3D_ptr = vbo_data_model_3D();
			vertices::Image3D* image_3D_ptr = vbo_data_image_3D();
			//apply
			for(uint32_t i = 0; i < m_vbo_size[2]; i++)
			{
				text_3D_ptr[i].m_position = m_model_matrix * text_3D_ptr[i].m_position;
			}
			for(uint32_t i = 0; i < m_vbo_size[0]; i++)
			{
				model_3D_ptr[i].m_position = m_model_matrix * model_3D_ptr[i].m_position;
			}
			for(uint32_t i = 0; i < m_vbo_size[1]; i++)
			{
				image_3D_ptr[i].m_position = m_model_matrix * image_3D_ptr[i].m_position;
			}
		}
	}
}