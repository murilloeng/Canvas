#pragma once

//std
#include <vector>

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
			Tessellator(void);

			//destructor
			~Tessellator(void);

			//data
			vec2& point(unsigned);
			std::vector<vec2>& points(void);
			const std::vector<vec2>& points(void) const;

			std::vector<unsigned>& loops(void);
			const std::vector<unsigned>& loops(void) const;

			const std::vector<unsigned>& triangles(void) const;

			//mesh
			void tessellate(void);
			static void tessellate(const vec2*, unsigned*, unsigned);
			static void tessellate(const vec3*, unsigned*, unsigned);
		
		private:
			//mesh
			void check(void);
			void setup_link(void);
			void setup_list(void);
			bool angle(unsigned, unsigned, unsigned);
			bool inside(unsigned, unsigned, unsigned, unsigned);

			//mesh
			static bool area_sign(const vec2*, unsigned);
			static bool area_sign(unsigned, unsigned, unsigned, const vec2*, bool);
			static bool vertex_inside(unsigned, unsigned, unsigned, unsigned, const vec2*, bool);

			//data
			std::vector<vec2> m_points;
			std::vector<unsigned> m_list;
			std::vector<unsigned> m_loops;
			std::vector<unsigned> m_links[2];
			std::vector<unsigned> m_triangles;
		};
	}
}