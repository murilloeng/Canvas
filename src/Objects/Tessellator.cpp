//std
#include <cfloat>
#include <cstdio>
#include <cstdlib>

//canvas
#include "Canvas/inc/Objects/Tessellator.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Tessellator::Tessellator(void) : m_loops({0})
		{
			return;
		}

		//destructor
		Tessellator::~Tessellator(void)
		{
			return;
		}

		//data
		vec2& Tessellator::point(unsigned index)
		{
			return m_points[index];
		}
		std::vector<vec2>& Tessellator::points(void)
		{
			return m_points;
		}
		const std::vector<vec2>& Tessellator::points(void) const
		{
			return m_points;
		}

		std::vector<unsigned>& Tessellator::loops(void)
		{
			return m_loops;
		}
		const std::vector<unsigned>& Tessellator::loops(void) const
		{
			return m_loops;
		}

		const std::vector<unsigned>& Tessellator::triangles(void) const
		{
			return m_triangles;
		}

		//mesh
		void Tessellator::tessellate(void)
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
		void Tessellator::tessellate(const vec2* vertices, unsigned* triangles, unsigned vertices_count)
		{
			//data
			unsigned index = 0;
			unsigned triangles_count = 0;
			const bool sign = area_sign(vertices, vertices_count);
			unsigned* list = (unsigned*) alloca(vertices_count * sizeof(unsigned));
			//list
			for(unsigned i = 0; i < vertices_count; i++) list[i] = i;
			//earcut
			while(true)
			{
				//candidate
				const unsigned p0 = list[index + 0];
				const unsigned p1 = list[index + 1];
				const unsigned p2 = list[index + 2];
				//check
				if(!area_sign(p0, p1, p2, vertices, sign))
				{
					index = (index + 1) % vertices_count;
					continue;
				}
				bool test = true;
				for(unsigned i = 0; i < vertices_count; i++)
				{
					unsigned pc = list[i];
					if(pc != p0 && pc != p1 && pc != p2)
					{
						test = test && !vertex_inside(pc, p0, p1, p2, vertices, sign);
					}
				}
				if(!test)
				{
					index = (index + 1) % vertices_count;
					continue;
				}
				//triangle
				triangles[3 * triangles_count + 0] = p0;
				triangles[3 * triangles_count + 1] = p1;
				triangles[3 * triangles_count + 2] = p2;
				//update
				vertices_count--;
				triangles_count++;
				for(unsigned i = index + 1; i < vertices_count; i++) list[i] = list[i + 1];
				//break
				index = 0;
				if(vertices_count < 3) break;
			}
		}
		void Tessellator::tessellate(const vec3* vertices, unsigned* triangles, unsigned vertices_count)
		{
			//data
			vec3 normal, t1, t2;
			vec2* vertices_2D = (vec2*) alloca(vertices_count * sizeof(vec2));
			//normal
			for(unsigned i = 0; i < vertices_count - 2; i++)
			{
				const vec3& v0 = vertices[i + 0];
				const vec3& v1 = vertices[i + 1];
				const vec3& v2 = vertices[i + 2];
				const float s1 = (v1 - v0).norm();
				const float s2 = (v2 - v0).norm();
				const vec3 nc = (v1 - v0).cross(v2 - v0);
				if(nc.norm() > 1e-8 * s1 * s2) { normal = nc; break; }
			}
			//vertices
			(normal /= normal.norm()).triad(t1, t2);
			for(unsigned i = 0; i < vertices_count; i++)
			{
				vertices_2D[i][0] = (vertices[i] - vertices[0]).inner(t1);
				vertices_2D[i][1] = (vertices[i] - vertices[0]).inner(t2);
			}
			//tessellation
			tessellate(vertices_2D, triangles, vertices_count);
		}

		//mesh
		void Tessellator::check(void)
		{
			//size
			if(m_loops.size() < 2)
			{
				printf("Error: Tessellator must have at least one loop!\n");
				exit(EXIT_FAILURE);
			}
			for(unsigned i = 0; i < m_loops.size() - 1; i++)
			{
				if(m_loops[i + 1] - m_loops[i] < 3)
				{
					printf("Error: Tessellator's loop %d does not have enough points!\n", i);
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
					printf("Error: Tessellator's loop %d has the same direction as outer loop!\n", i);
					exit(EXIT_FAILURE);
				}
			}
		}
		void Tessellator::setup_link(void)
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
		void Tessellator::setup_list(void)
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
		bool Tessellator::angle(unsigned p0, unsigned p1, unsigned p2)
		{
			return (m_points[p1] - m_points[p0]).cross(m_points[p2] - m_points[p0]) >= 0;
		}
		bool Tessellator::inside(unsigned pc, unsigned p0, unsigned p1, unsigned p2)
		{
			return angle(p0, p1, pc) && angle(p1, p2, pc) && angle(p2, p0, pc);
		}

		//mesh
		bool Tessellator::area_sign(const vec2* vertices, unsigned vertices_count)
		{
			float A = 0;
			const vec2& v0 = vertices[0];
			for (unsigned i = 0; i < vertices_count - 2; i++)
			{
				A += (vertices[i + 1] - v0).cross(vertices[i + 2] - v0);
			}
			return A > 0;
		}
		bool Tessellator::area_sign(unsigned p0, unsigned p1, unsigned p2, const vec2* vertices, bool sign)
		{
			const int s = sign ? +1 : -1;
			const vec2& v0 = vertices[p0];
			const vec2& v1 = vertices[p1];
			const vec2& v2 = vertices[p2];
			return s * (v1 - v0).cross(v2 - v0) >= 0;
		}
		bool Tessellator::vertex_inside(unsigned pc, unsigned p0, unsigned p1, unsigned p2, const vec2* vertices, bool sign)
		{
			return 
				area_sign(p0, p1, pc, vertices, sign) && 
				area_sign(p1, p2, pc, vertices, sign) && 
				area_sign(p2, p0, pc, vertices, sign);
		}
	}
}