//std
#include <cmath>
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Image.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Image::Image(void) : m_shader{{
			new shaders::Stage(GL_VERTEX_SHADER, "image3D.vert"),
			new shaders::Stage(GL_FRAGMENT_SHADER, "image3D.frag")
		}}
		{
			//vbo setup
			m_vbo.vertex_size(sizeof(vertices::Image3D));
			//vao setup
			m_vao.attribute_enable(0);
			m_vao.attribute_enable(1);
			m_vao.attribute_binding(0, 0);
			m_vao.attribute_binding(1, 0);
			m_vao.attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
			m_vao.attribute_format(1, 2, GL_FLOAT, 3 * sizeof(float));
			m_vao.vertex_buffer(0, m_vbo.id(), 0, sizeof(vertices::Image3D));
			//vbo allocate
			m_vbo.allocate(4);
		}

		//destructor
		Image::~Image(void)
		{
			return;
		}

		//data
		Anchor Image::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Image::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		textures::Image& Image::image(void)
		{
			return m_image;
		}

		//draw
		void Image::setup(void)
		{
			//data
			const float w = m_image.texture().width();
			const float h = m_image.texture().height();
			const float x2 = -h / 2 * uint32_t(m_anchor.vertical());
			const float x1 = -w / 2 * uint32_t(m_anchor.horizontal());
			vertices::Image3D* vbo_ptr = (vertices::Image3D*) m_vbo.data();
			//texture coordinates
			vbo_ptr[0].m_texture_coordinates = {0, 0};
			vbo_ptr[1].m_texture_coordinates = {1, 0};
			vbo_ptr[2].m_texture_coordinates = {1, 1};
			vbo_ptr[3].m_texture_coordinates = {0, 1};
			//positions
			const float m = fmaxf(w, h);
			vbo_ptr[0].m_position = {(x1 + 0) / m, (x2 + 0) / m, 0};
			vbo_ptr[1].m_position = {(x1 + w) / m, (x2 + 0) / m, 0};
			vbo_ptr[2].m_position = {(x1 + w) / m, (x2 + h) / m, 0};
			vbo_ptr[3].m_position = {(x1 + 0) / m, (x2 + h) / m, 0};
			//transfer
			apply_model();
			m_vbo.transfer();
		}
		void Image::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			m_image.texture().bind_unit(0);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		}

		//model
		void Image::apply_model(void) const
		{
			//data
			vertices::Image3D* vbo_ptr = (vertices::Image3D*) m_vbo.data();
			//model
			if(!m_has_model_matrix) return;
			for(uint32_t i = 0; i < 4; i++)
			{
				vbo_ptr[i].m_position *= m_model_matrix;
			}
		}
	}
}