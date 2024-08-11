#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Math/vec3.hpp"

namespace canvas
{
	namespace objects
	{
		class Tessellator
		{
		public:
			//constructor
			Tessellator(const vec2*, const uint32_t*, uint32_t, uint32_t*);
			Tessellator(const vec3*, const uint32_t*, uint32_t, uint32_t*);

			//destructor
			~Tessellator(void);

			//data
			uint32_t* triangles(void) const;
			uint32_t loops_count(void) const;
			const vec2* vertices(void) const;
			const uint32_t* loops(void) const;
			const vec2& vertex(uint32_t) const;

			//tessellation
			void tessellate(void);

		private:
			//tessellation
			void tessellate_2D(void);
			void tessellate_3D(void);

			bool check(void) const;
			bool area_sign(uint32_t) const;
			void setup_list(uint32_t*) const;
			void setup_links(uint32_t*) const;

			bool is_ear(uint32_t, const uint32_t*, uint32_t, bool) const;
			bool is_vertex_in_triangle(uint32_t, uint32_t, uint32_t, uint32_t) const;

			void list_add_loop(uint32_t*, uint32_t&, uint32_t, uint32_t, uint32_t) const;

			//data
			uint32_t* m_triangles;
			uint32_t m_loops_count;
			const uint32_t* m_loops;
			const vec2* m_vertices_2D;
			const vec3* m_vertices_3D;
		};
	}
}