//std
#include <cmath>

//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/1D/Polyline.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Polyline::Polyline(void)
		{
			return;
		}

		//destructor
		Polyline::~Polyline(void)
		{
			return;
		}

		//data
		std::vector<vec3>& Polyline::vertices(void)
		{
			return m_vertices;
		}
		const std::vector<vec3>& Polyline::vertices(void) const
		{
			return m_vertices;
		}

		//draw
		void Polyline::draw(void)
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_LINE_STRIP, 0, m_vertices.size());
		}
		void Polyline::setup(void)
		{
			m_vbo.allocate(m_vertices.size());
		}
		void Polyline::update(void)
		{
			//data
			const uint32_t nv = m_vertices.size();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < nv; i++)
			{
				vbo_ptr[i].m_color = m_color_stroke;
				vbo_ptr[i].m_position = m_vertices[i];
			}
			//transfer
			apply_model();
			m_vbo.transfer();
		}
	}
}