//Canvas
#include "Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Cameras/BoundingBox.hpp"
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		BaseModel3D::BaseModel3D(void) : m_shader{"Model3D"}, m_color_fill{"blue"}, m_color_stroke{"white"}
		{
			//vbo setup
			m_vbo.vertex_size(sizeof(vertices::Model3D));
			//vao setup
			m_vao.attribute_enable(0);
			m_vao.attribute_enable(1);
			m_vao.attribute_binding(0, 0);
			m_vao.attribute_binding(1, 0);
			m_vao.element_buffer(m_ibo.id());
			m_vao.attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
			m_vao.attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
			m_vao.vertex_buffer(0, m_vbo.id(), 0, sizeof(vertices::Model3D));
		}

		//destructor
		BaseModel3D::~BaseModel3D(void)
		{
			return;
		}

		//data
		Color BaseModel3D::color_fill(void) const
		{
			return m_color_fill;
		}
		Color BaseModel3D::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color BaseModel3D::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color BaseModel3D::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}

		//model
		void BaseModel3D::apply_model(void) const
		{
			//data
			const uint32_t nv = m_vbo.vertex_count();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//apply
			if(!m_has_model_matrix) return;
			for(uint32_t i = 0; i < nv; i++)
			{
				vbo_ptr[i].m_position *= m_model_matrix;
			}
		}

		//update
		void BaseModel3D::update_bounding_box(cameras::BoundingBox& bounding_box) const
		{
			//data
			const uint32_t nv = m_vbo.vertex_count();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//update
			for(uint32_t i = 0; i < nv; i++)
			{
				bounding_box.insert_vertex(vbo_ptr[i].m_position.data());
			}
		}
	}
}