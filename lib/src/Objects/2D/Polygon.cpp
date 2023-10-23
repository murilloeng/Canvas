//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/2D/Polygon.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Polygon::Polygon(void) : m_loops{0}
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
			return m_points;
		}
		const std::vector<vec2>& Polygon::points(void) const
		{
			return m_points;
		}

		std::vector<unsigned>& Polygon::loops(void)
		{
			return m_loops;
		}
		const std::vector<unsigned>& Polygon::loops(void) const
		{
			return m_loops;
		}

		//buffers
		unsigned Polygon::vbo_size(unsigned index) const
		{
			return m_points.size() * (m_stroke + m_fill) * (index == 0);
		}
		unsigned Polygon::ibo_size(unsigned index) const
		{
			const unsigned nl = m_loops.back();
			const unsigned nt = m_loops.back() + 2 * m_loops.size() - 6;
			return nl * m_stroke * (index == 1) + nt * m_fill * (index == 2);
		}

		//topology
		bool Polygon::angle(unsigned p0, unsigned p1, unsigned p2) const
		{
			return (m_points[p1] - m_points[p0]).cross(m_points[p2] - m_points[p0]) >= 0;
		}
		bool Polygon::inside(unsigned pc, unsigned p0, unsigned p1, unsigned p2) const
		{
			return angle(p0, p1, pc) && angle(p1, p2, pc) && angle(p2, p0, pc);
		}

		//draw
		void Polygon::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			const unsigned nt = m_triangles.size() / 3;
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
			unsigned vbo_index = m_vbo_index[0] + m_stroke * m_loops.back();
			//ibo data
			for(unsigned i = 0; i < nt; i++)
			{
				ibo_ptr[0] = vbo_index + m_triangles[3 * i + 0];
				ibo_ptr[1] = vbo_index + m_triangles[3 * i + 1];
				ibo_ptr[2] = vbo_index + m_triangles[3 * i + 2];
				ibo_ptr += 3;
			}
		}
		void Polygon::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned vbo_index = m_vbo_index[0];
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//ibo data
			for(unsigned i = 0; i + 1 < m_loops.size(); i++)
			{
				const unsigned ls = m_loops[i + 1] - m_loops[i];
				for(unsigned j = m_loops[i]; j < m_loops[i + 1]; j++)
				{
					ibo_ptr[0] = vbo_index + m_loops[i] + (j + 0 - m_loops[i]) % ls;
					ibo_ptr[1] = vbo_index + m_loops[i] + (j + 1 - m_loops[i]) % ls;
					ibo_ptr += 2;
				}
			}
		}
		void Polygon::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0] + m_stroke * m_points.size();
			//vbo data
			for(unsigned i = 0; i < m_points.size(); i++)
			{
				(vbo_ptr + i)->m_color = m_color_fill;
				(vbo_ptr + i)->m_position = {m_points[i][0], m_points[i][1], 0};
			}
		}
		void Polygon::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			for(unsigned i = 0; i < m_points.size(); i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = {m_points[i][0], m_points[i][1], 0};
			}
		}

		void Polygon::setup_link(void)
		{
			m_links[0].resize(m_loops.size() - 2);
			m_links[1].resize(m_loops.size() - 2);
			for(unsigned i = 0; i < m_links[0].size(); i++)
			{
				float d = FLT_MAX;
				for(unsigned po = m_loops[0]; po < m_loops[1]; po++)
				{
					for(unsigned pi = m_loops[i + 1]; pi < m_loops[i + 2]; pi++)
					{
						if((m_points[pi] - m_points[po]).norm() < d)
						{
							m_links[0][i] = po;
							m_links[1][i] = pi;
							d = (m_points[pi] - m_points[po]).norm();
						}
					}
				}
			}
		}
		void Polygon::setup_list(void)
		{
			m_list.clear();
			m_triangles.clear();
			for(unsigned i = m_loops[0]; i < m_loops[1]; i++)
			{
				m_list.push_back(i);
				for(unsigned j = 0; j < m_links[0].size(); j++)
				{
					if(m_links[0][j] == i)
					{
						const unsigned a = m_links[1][j] - m_loops[j + 1];
						const unsigned s = m_loops[j + 2] - m_loops[j + 1];
						for(unsigned k = 0; k <= s; k++)
						{
							m_list.push_back(m_loops[j + 1] + (a + k) % s);
						}
						m_list.push_back(i);
					}
				}
			}
		}
		void Polygon::setup_triangles(void)
		{
			//data
			unsigned index = 0;
			//earcut
			while(true)
			{
				//candidate
				const unsigned p0 = m_list[(index + 0) % m_list.size()];
				const unsigned p1 = m_list[(index + 1) % m_list.size()];
				const unsigned p2 = m_list[(index + 2) % m_list.size()];
				//check
				if(!angle(p0, p1, p2))
				{
					index++;
					continue;
				}
				bool test = true;
				for(unsigned pc : m_list)
				{
					test = test && (p0 == pc || p1 == pc || p2 == pc || !inside(pc, p0, p1, p2));
				}
				if(!test)
				{
					index++;
					continue;
				}
				//triangle
				m_triangles.push_back(p0);
				m_triangles.push_back(p1);
				m_triangles.push_back(p2);
				m_list.erase(m_list.begin() + (index + 1) % m_list.size());
				if(m_list.size() < 3) break;
			}
		}
		void Polygon::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			setup_link();
			setup_list();
			setup_triangles();
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