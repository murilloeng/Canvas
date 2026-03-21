#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Polygon : public BaseModel3D
		{
		public:
			//constructors
			Polygon(void);

			//destructor
			~Polygon(void);

			//data
			std::vector<vec2>& vertices(void);
			const std::vector<vec2>& vertices(void) const;

			std::vector<uint32_t>& loops(void);
			const std::vector<uint32_t>& loops(void) const;

		protected:
			//data
			void ibo_fill_data(void) const;
			void vbo_fill_data(void) const;
			void ibo_stroke_data(void) const;
			void vbo_stroke_data(void) const;

			//draw
			void draw(void) override;
			void setup(void) override;
			void update(void) override;

			//data
			std::vector<vec2> m_vertices;
			std::vector<uint32_t> m_loops;
			std::vector<uint32_t> m_triangles;
		};
	}
}