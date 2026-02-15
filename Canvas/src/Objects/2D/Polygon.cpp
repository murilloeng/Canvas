//std
#include <cmath>
#include <cfloat>

//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/2D/Polygon.hpp"
#include "Canvas/Canvas/inc/Objects/Tessellator.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Polygon::Polygon(void)
		{
			return;
		}

		//destructor
		Polygon::~Polygon(void)
		{
			return;
		}

		//data
		Color Polygon::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Polygon::color_fill(const Color& color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Polygon::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Polygon::color_stroke(const Color& color_stroke)
		{
			return m_color_stroke = color_stroke;
		}

		std::vector<vec2>& Polygon::vertices(void)
		{
			return m_vertices;
		}
		const std::vector<vec2>& Polygon::vertices(void) const
		{
			return m_vertices;
		}

		std::vector<uint32_t>& Polygon::loops(void)
		{
			return m_loops;
		}
		const std::vector<uint32_t>& Polygon::loops(void) const
		{
			return m_loops;
		}

		//draw
		void Polygon::setup(void)
		{
			//data
			const uint32_t nl = (uint32_t) m_loops.size();
			const uint32_t nv = (uint32_t) m_vertices.size();
			uint32_t* triangles = (uint32_t*) alloca(3 * (nv + 2 * nl - 6) * sizeof(uint32_t));
			//allocate
			m_vbo.allocate(2 * nv);
			m_ibo.allocate(5 * nv + 6 * nl - 18);
			Tessellator(m_vertices.data(), m_loops.data(), nl - 1, triangles).tessellate();
			//buffers data
			uint32_t* ibo_ptr = m_ibo.data();
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) m_vbo.data();
			//vbo data
			for(uint32_t i = 0; i < nv; i++)
			{
				vbo_ptr[i].m_color = m_color_fill;
				vbo_ptr[i + nv].m_color = m_color_stroke;
				vbo_ptr[i].m_position = {m_vertices[i][0], m_vertices[i][1], 0};
				vbo_ptr[i + nv].m_position = {m_vertices[i][0], m_vertices[i][1], 0};
			}
			//ibo data
			for(uint32_t i = 0; i < nv + 2 * nl - 6; i++)
			{
				ibo_ptr[0] = triangles[3 * i + 0];
				ibo_ptr[1] = triangles[3 * i + 2];
				ibo_ptr[2] = triangles[3 * i + 1];
				ibo_ptr += 3;
			}
			for(uint32_t i = 0; i + 1 < m_loops.size(); i++)
			{
				const uint32_t ls = m_loops[i + 1] - m_loops[i];
				for(uint32_t j = m_loops[i]; j < m_loops[i + 1]; j++)
				{
					ibo_ptr[0] = m_loops[i] + (j + 0 - m_loops[i]) % ls;
					ibo_ptr[1] = m_loops[i] + (j + 1 - m_loops[i]) % ls;
					ibo_ptr += 2;
				}
			}
			//transfer
			m_vbo.transfer();
			m_ibo.transfer();
		}
		void Polygon::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			const uint32_t nl = (uint32_t) m_loops.size();
			const uint32_t nv = (uint32_t) m_vertices.size();
			glDrawElements(GL_TRIANGLES, 3 * (nv + 2 * nl - 6), GL_UNSIGNED_INT, nullptr);
			glDrawElementsBaseVertex(GL_LINES, 2 * nv, GL_UNSIGNED_INT, (void*) (3 * (nv + 2 * nl - 6) * sizeof(uint32_t)), nv);
		}
	}
}