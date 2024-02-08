#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec2.hpp"

namespace canvas
{
	namespace objects
	{
		class Tesselator
		{
		public:
			//constructor
			Tesselator(void);

			//destructor
			~Tesselator(void);

			//data
			vec2& point(unsigned);
			std::vector<vec2>& points(void);
			const std::vector<vec2>& points(void) const;

			std::vector<unsigned>& loops(void);
			const std::vector<unsigned>& loops(void) const;

			const std::vector<unsigned>& triangles(void) const;

			//mesh
			void tessellate(void);
		
		private:
			//mesh
			void check(void);
			void setup_link(void);
			void setup_list(void);
			bool angle(unsigned, unsigned, unsigned);
			bool inside(unsigned, unsigned, unsigned, unsigned);

			//data
			std::vector<vec2> m_points;
			std::vector<unsigned> m_list;
			std::vector<unsigned> m_loops;
			std::vector<unsigned> m_links[2];
			std::vector<unsigned> m_triangles;
		};
	}
}