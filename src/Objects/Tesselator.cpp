//std
#include <cfloat>
#include <cstdio>
#include <cstdlib>

//canvas
#include "Canvas/inc/Objects/Tesselator.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Tesselator::Tesselator(void) : m_loops({0})
		{
			return;
		}

		//destructor
		Tesselator::~Tesselator(void)
		{
			return;
		}

		//data
		vec2& Tesselator::point(unsigned index)
		{
			return m_points[index];
		}
		std::vector<vec2>& Tesselator::points(void)
		{
			return m_points;
		}
		const std::vector<vec2>& Tesselator::points(void) const
		{
			return m_points;
		}

		std::vector<unsigned>& Tesselator::loops(void)
		{
			return m_loops;
		}
		const std::vector<unsigned>& Tesselator::loops(void) const
		{
			return m_loops;
		}

		const std::vector<unsigned>& Tesselator::triangles(void) const
		{
			return m_triangles;
		}

		//mesh
		void Tesselator::tessellate(void)
		{
			//data
			unsigned index = 0;
			//setup
			check();
			setup_link();
			setup_list();
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

		//mesh
		void Tesselator::check(void)
		{
			//size
			if(m_loops.size() < 2)
			{
				printf("Error: Tesselator must have at least one loop!\n");
				exit(EXIT_FAILURE);
			}
			for(unsigned i = 0; i < m_loops.size() - 1; i++)
			{
				if(m_loops[i + 1] - m_loops[i] < 3)
				{
					printf("Error: Tesselator's loop %d does not have enough points!\n", i);
					exit(EXIT_FAILURE);
				}
			}
			//direction
			double A_outer = 0;
			for(unsigned i = 0; i + 2 < m_loops[1]; i++)
			{
				A_outer += (m_points[i + 1] - m_points[0]).cross(m_points[i + 2] - m_points[0]);
			}
			for(unsigned i = 1; i + 1 < m_loops.size(); i++)
			{
				double A_inner = 0;
				const vec2 xr = m_points[m_loops[i]];
				for(unsigned j = m_loops[i]; j + 2 < m_loops[i + 1]; j++)
				{
					A_inner += (m_points[j + 1] - xr).cross(m_points[j + 2] - xr);
				}
				if(A_inner * A_outer > 0)
				{
					printf("Error: Tesselator's loop %d has the same direction as outer loop!\n", i);
					exit(EXIT_FAILURE);
				}
			}
		}
		void Tesselator::setup_link(void)
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
		void Tesselator::setup_list(void)
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
		bool Tesselator::angle(unsigned p0, unsigned p1, unsigned p2)
		{
			return (m_points[p1] - m_points[p0]).cross(m_points[p2] - m_points[p0]) >= 0;
		}
		bool Tesselator::inside(unsigned pc, unsigned p0, unsigned p1, unsigned p2)
		{
			return angle(p0, p1, pc) && angle(p1, p2, pc) && angle(p2, p0, pc);
		}
	}
}