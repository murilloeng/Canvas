//std
#include <cmath>
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Objects/Image/Latex.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Latex::Latex(void) : m_color{"white"}, 
			m_shader{{new shaders::Stage(GL_VERTEX_SHADER, "text3D.vert"), new shaders::Stage(GL_FRAGMENT_SHADER, "text3D.frag")}}
		{
			//vao setup
			m_vao.attribute_enable(0);
			m_vao.attribute_enable(1);
			m_vao.attribute_enable(2);
			m_vao.attribute_binding(0, 0);
			m_vao.attribute_binding(1, 0);
			m_vao.attribute_binding(2, 0);
			m_vao.attribute_format(0, 3, GL_FLOAT, 0 * sizeof(float));
			m_vao.attribute_format(1, 4, GL_FLOAT, 3 * sizeof(float));
			m_vao.attribute_format(2, 2, GL_FLOAT, 7 * sizeof(float));
			m_vao.vertex_buffer(0, m_vbo.id(), 0, sizeof(vertices::Text3D));
			//vbo setup
			m_vbo.vertex_count(4);
			m_vbo.vertex_size(sizeof(vertices::Text3D));
			//allocate
			m_vbo.allocate();
		}

		//destructor
		Latex::~Latex(void)
		{
			return;
		}

		//data
		Anchor Latex::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Latex::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		Color Latex::color(void) const
		{
			return m_color;
		}
		Color Latex::color(const Color& color)
		{
			return m_color = color;
		}

		textures::Latex& Latex::latex(void)
		{
			return m_latex;
		}

		//draw
		void Latex::setup(void)
		{
			//data
			const float w = m_latex.texture().width();
			const float h = m_latex.texture().height();
			const float x2 = -h / 2 * uint32_t(m_anchor.vertical());
			const float x1 = -w / 2 * uint32_t(m_anchor.horizontal());
			vertices::Text3D* vbo_ptr = (vertices::Text3D*) m_vbo.data();
			//color
			vbo_ptr[0].m_color = m_color;
			vbo_ptr[1].m_color = m_color;
			vbo_ptr[2].m_color = m_color;
			vbo_ptr[3].m_color = m_color;
			//texture coordinates
			vbo_ptr[0].m_texture_coordinates = {0, 0};
			vbo_ptr[1].m_texture_coordinates = {1, 0};
			vbo_ptr[2].m_texture_coordinates = {1, 1};
			vbo_ptr[3].m_texture_coordinates = {0, 1};
			//positions
			const float m = fmaxf(w, h);
			vbo_ptr[0].m_position = vec3((x1 + 0) / m, (x2 + 0) / m, 0);
			vbo_ptr[1].m_position = vec3((x1 + w) / m, (x2 + 0) / m, 0);
			vbo_ptr[2].m_position = vec3((x1 + w) / m, (x2 + h) / m, 0);
			vbo_ptr[3].m_position = vec3((x1 + 0) / m, (x2 + h) / m, 0);
			//transfer
			apply_model();
			m_vbo.transfer();
		}
		void Latex::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			m_latex.texture().bind_unit(0);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		}

		//model
		void Latex::apply_model(void) const
		{
			//data
			vertices::Text3D* vbo_ptr = (vertices::Text3D*) m_vbo.data();
			//model
			if(!m_has_model_matrix) return;
			for(uint32_t i = 0; i < 4; i++)
			{
				vbo_ptr[i].m_position *= m_model_matrix;
			}
		}
	}
}