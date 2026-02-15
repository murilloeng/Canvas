#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Polygon : public Model3D
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
			void setup(void) override;
			void draw(void) const override;

			//data
			std::vector<vec2> m_vertices;
			std::vector<uint32_t> m_loops;
		};
	}
}