//std
#include <cmath>
#include <cfloat>

//canvas
#include "Canvas/inc/Vertices/Model.hpp"

#include "Canvas/inc/Objects/2D/Polygon.hpp"

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
		std::vector<vec2>& Polygon::points(void)
		{
			return m_tesselator.points();
		}
		const std::vector<vec2>& Polygon::points(void) const
		{
			return m_tesselator.points();
		}

		std::vector<unsigned>& Polygon::loops(void)
		{
			return m_tesselator.loops();
		}
		const std::vector<unsigned>& Polygon::loops(void) const
		{
			return m_tesselator.loops();
		}

		//buffers
		unsigned Polygon::vbo_size(unsigned index) const
		{
			const unsigned np = m_tesselator.points().size();
			return (unsigned) np * (m_stroke + m_fill) * (index == 0);
		}
		unsigned Polygon::ibo_size(unsigned index) const
		{
			const unsigned nl = m_tesselator.loops().back();
			const unsigned ns = m_tesselator.loops().size();
			return nl * m_stroke * (index == 1) + (nl + 2 * ns - 6) * m_fill * (index == 2);
		}

		//draw
		void Polygon::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			const std::vector<unsigned>& triangles = m_tesselator.triangles();
			unsigned vbo_index = m_vbo_index[0] + m_stroke * m_tesselator.loops().back();
			//ibo data
			for(unsigned i = 0; i < triangles.size() / 3; i++)
			{
				ibo_ptr[0] = vbo_index + triangles[3 * i + 0];
				ibo_ptr[1] = vbo_index + triangles[3 * i + 2];
				ibo_ptr[2] = vbo_index + triangles[3 * i + 1];
				ibo_ptr += 3;
			}
		}
		void Polygon::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned vbo_index = m_vbo_index[0];
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			const std::vector<unsigned>& loops = m_tesselator.loops();
			//ibo data
			for(unsigned i = 0; i + 1 < loops.size(); i++)
			{
				const unsigned ls = loops[i + 1] - loops[i];
				for(unsigned j = loops[i]; j < loops[i + 1]; j++)
				{
					ibo_ptr[0] = vbo_index + loops[i] + (j + 0 - loops[i]) % ls;
					ibo_ptr[1] = vbo_index + loops[i] + (j + 1 - loops[i]) % ls;
					ibo_ptr += 2;
				}
			}
		}
		void Polygon::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			const std::vector<vec2>& points = m_tesselator.points();
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0] + m_stroke * points.size();
			//vbo data
			for(unsigned i = 0; i < points.size(); i++)
			{
				(vbo_ptr + i)->m_color = m_color_fill;
				(vbo_ptr + i)->m_position = {points[i][0], points[i][1], 0};
			}
		}
		void Polygon::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			const std::vector<vec2>& points = m_tesselator.points();
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(unsigned i = 0; i < points.size(); i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = {points[i][0], points[i][1], 0};
			}
		}

		void Polygon::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			m_tesselator.tessellate();
			Object::setup(vbo_counter, ibo_counter);
		}
		void Polygon::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}