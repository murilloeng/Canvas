//Canvas
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Cameras/BoundingBox.hpp"
#include "Canvas/Canvas/inc/Objects/Bases/BaseText3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		BaseText3D::BaseText3D(void) : m_shader{"Text3D"}
		{
			//vbo setup
			m_vbo.vertex_size(sizeof(vertices::Text3D));
			//vao setup
			m_vao.attribute_enable(0);
			m_vao.attribute_enable(1);
			m_vao.attribute_enable(2);
			m_vao.attribute_binding(0, 0);
			m_vao.attribute_binding(1, 0);
			m_vao.attribute_binding(2, 0);
			m_vao.element_buffer(m_ibo.id());
			m_vao.attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
			m_vao.attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
			m_vao.attribute_format(2, 2, GL_FLOAT, 7 * sizeof(float));
			m_vao.vertex_buffer(0, m_vbo.id(), 0, sizeof(vertices::Text3D));
		}

		//destructor
		BaseText3D::~BaseText3D(void)
		{
			return;
		}

		//model
		void BaseText3D::apply_model(void) const
		{
			//data
			const uint32_t nv = m_vbo.vertex_count();
			vertices::Text3D* vbo_ptr = (vertices::Text3D*) m_vbo.data();
			//apply
			if(!m_has_model_matrix) return;
			for(uint32_t i = 0; i < nv; i++)
			{
				vbo_ptr[i].m_position *= m_model_matrix;
			}
		}

		//update
		void BaseText3D::update_bounding_box(cameras::BoundingBox& bounding_box) const
		{
			//data
			const uint32_t nv = m_vbo.vertex_count();
			vertices::Text3D* vbo_ptr = (vertices::Text3D*) m_vbo.data();
			//update
			for(uint32_t i = 0; i < nv; i++)
			{
				bounding_box.insert_vertex(vbo_ptr[i].m_position.data());
			}
		}
	}
}