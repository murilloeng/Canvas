//std
#include <cmath>
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
		Tessellator::Tessellator(const vec2* vertices_2D, const uint32_t* loops, uint32_t loops_count, uint32_t* triangles) : 
			m_triangles(triangles), m_loops_count(loops_count), m_loops(loops), m_vertices_2D(vertices_2D), m_vertices_3D(nullptr)
		{
			return;
		}
		Tessellator::Tessellator(const vec3* vertices_3D, const uint32_t* loops, uint32_t loops_count, uint32_t* triangles) : 
			m_triangles(triangles), m_loops_count(loops_count), m_loops(loops), m_vertices_2D(nullptr), m_vertices_3D(vertices_3D)
		{
			return;
		}

		//destructor
		Tessellator::~Tessellator(void)
		{
			return;
		}

		//data
		uint32_t* Tessellator::triangles(void) const
		{
			return m_triangles;
		}
		uint32_t Tessellator::loops_count(void) const
		{
			return m_loops_count;
		}
		const vec2* Tessellator::vertices(void) const
		{
			return m_vertices_2D;
		}
		const uint32_t* Tessellator::loops(void) const
		{
			return m_loops;
		}
		const vec2& Tessellator::vertex(uint32_t index) const
		{
			return m_vertices_2D[index];
		}

		//tessellation
		void Tessellator::tessellate(void)
		{
			m_vertices_3D ? tessellate_3D() : tessellate_2D();
		}

		void Tessellator::tessellate_2D(void)
		{
			//data
			uint32_t index = 0;
			uint32_t triangles_count = 0;
			const bool sign = area_sign(0);
			const uint32_t nl = m_loops_count;
			uint32_t list_size = m_loops[nl] + 2 * (nl - 1);
			uint32_t* list = (uint32_t*) alloca(list_size * sizeof(uint32_t));
			//check
			if(!check()) exit(EXIT_FAILURE);
			//tessellate
			setup_list(list);
			while(list_size >= 3)
			{
				if(is_ear(index, list, list_size, sign))
				{
					//triangle
					m_triangles[3 * triangles_count + 0] = list[(index + 0) % list_size];
					m_triangles[3 * triangles_count + 1] = list[(index + 1) % list_size];
					m_triangles[3 * triangles_count + 2] = list[(index + 2) % list_size];
					//list
					list_size--;
					for(uint32_t i = index + 1; i < list_size; i++) list[i] = list[i + 1];
					//update
					index = 0;
					triangles_count++;
				}
				else
				{
					index = (index + 1) % list_size;
				}
			}
		}
		void Tessellator::tessellate_3D(void)
		{
			//data
			vec3 normal, t1, t2;
			const uint32_t nv = m_loops[m_loops_count];
			vec2* vertices_2D = (vec2*) alloca(nv * sizeof(vec2));
			//normal
			for(uint32_t i = 0; i < nv - 2; i++)
			{
				const vec3& v0 = m_vertices_3D[i + 0];
				const vec3& v1 = m_vertices_3D[i + 1];
				const vec3& v2 = m_vertices_3D[i + 2];
				normal = (v1 - v0).cross(v2 - v0);
				const float s1 = (v1 - v0).norm();
				const float s2 = (v2 - v0).norm();
				if(normal.norm() > 1e-5 * fmaxf(s1, s2)) break;
			}
			//projection
			normal.unit().triad(t1, t2);
			for(uint32_t i = 0; i < nv; i++)
			{
				vertices_2D[i][0] = (m_vertices_3D[i] - m_vertices_3D[0]).inner(t1);
				vertices_2D[i][1] = (m_vertices_3D[i] - m_vertices_3D[0]).inner(t2);
			}
			//tessellation
			m_vertices_2D = vertices_2D; tessellate_2D();
		}

		bool Tessellator::check(void) const
		{
			const bool s0 = area_sign(0);
			for(uint32_t loop_index = 1; loop_index < m_loops_count; loop_index++)
			{
				if(area_sign(loop_index) == s0) return false;
			}
			return true;
		}
		bool Tessellator::area_sign(uint32_t loop_index) const
		{
			//data
			float A = 0;
			const uint32_t loop_size = m_loops[loop_index + 1] - m_loops[loop_index];
			//area
			for(uint32_t i = 0; i < loop_size; i++)
			{
				const vec2& v0 = m_vertices_2D[m_loops[loop_index] + (i + 0) % loop_size];
				const vec2& v1 = m_vertices_2D[m_loops[loop_index] + (i + 1) % loop_size];
				A += v0.cross(v1);
			}
			//return
			return A > 0;
		}
		void Tessellator::setup_list(uint32_t* list) const
		{
			//data
			uint32_t* links = (uint32_t*) alloca(2 * (m_loops_count - 1) * sizeof(uint32_t));
			//list
			setup_links(links);
			uint32_t list_size = m_loops[1];
			for(uint32_t i = 0; i < m_loops[1]; i++)
			{
				list[i] = i;
			}
			for(uint32_t i = 1; i < m_loops_count; i++)
			{
				for(uint32_t j = 0; j < list_size; j++)
				{
					if(list[j] == links[2 * (i - 1) + 0])
					{
						list_add_loop(list, list_size, j, i, links[2 * (i - 1) + 1]);
						break;
					}
				}
			}
		}
		void Tessellator::setup_links(uint32_t* links) const
		{
			for(uint32_t i = 1; i < m_loops_count; i++)
			{
				float d = FLT_MAX;
				for(uint32_t j = m_loops[0]; j < m_loops[1]; j++)
				{
					for(uint32_t k = m_loops[i]; k < m_loops[i + 1]; k++)
					{
						const vec2& v0 = m_vertices_2D[j];
						const vec2& v1 = m_vertices_2D[k];
						if(d > (v1 - v0).norm())
						{
							d = (v1 - v0).norm();
							links[2 * (i - 1) + 0] = j;
							links[2 * (i - 1) + 1] = k - m_loops[i];
						}
					}
				}
			}
		}

		bool Tessellator::is_ear(uint32_t index, const uint32_t* list, uint32_t list_size, bool sign) const
		{
			//data
			const int s = sign ? +1 : -1;
			const uint16_t i0 = list[(index + 0) % list_size];
			const uint16_t i1 = list[(index + 1) % list_size];
			const uint16_t i2 = list[(index + 2) % list_size];
			//check sign
			const vec2& v0 = m_vertices_2D[i0];
			const vec2& v1 = m_vertices_2D[i1];
			const vec2& v2 = m_vertices_2D[i2];
			if(s * (v1 - v0).cross(v2 - v0) <= 0) return false;
			//check vertices
			for(uint32_t i = 0; i < list_size; i++)
			{
				uint32_t ip = list[i];
				if(ip != i0 && ip != i1 && ip != i2 && is_vertex_in_triangle(ip, i0, i1, i2))
				{
					return false;
				}
			}
			//return
			return true;
		}
		bool Tessellator::is_vertex_in_triangle(uint32_t ip, uint32_t i0, uint32_t i1, uint32_t i2) const
		{
			const vec2& vp = m_vertices_2D[ip];
			const vec2& v0 = m_vertices_2D[i0];
			const vec2& v1 = m_vertices_2D[i1];
			const vec2& v2 = m_vertices_2D[i2];
			const float a0 = (v0 - vp).cross(v1 - vp);
			const float a1 = (v1 - vp).cross(v2 - vp);
			const float a2 = (v2 - vp).cross(v0 - vp);
			return (a0 >= 0 && a1 >= 0 && a2 >= 0) || (a0 <= 0 && a1 <= 0 && a2 <= 0);
		}

		void Tessellator::list_add_loop(uint32_t* list, uint32_t& list_size, uint32_t list_index, uint32_t loop_index, uint32_t loop_link) const
		{
			//data
			const uint32_t loop_size = m_loops[loop_index + 1] - m_loops[loop_index];
			//shift
			for(uint32_t i = 0; i < list_size - list_index - 1; i++)
			{
				list[list_size - i + loop_size + 1] = list[list_size - i - 1];
			}
			//update
			list_size += loop_size + 2;
			for(uint32_t i = 0; i < loop_size; i++)
			{
				list[list_index + 1 + i] = m_loops[loop_index] + (loop_link + i) % loop_size;
			}
			list[list_index + loop_size + 2] = list[list_index];
			list[list_index + loop_size + 1] = m_loops[loop_index] + loop_link;
		}
	}
}