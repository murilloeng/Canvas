#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec2.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Polygon : public Geometry
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

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			std::vector<vec2> m_vertices;
			std::vector<uint32_t> m_loops;
		};
	}
}