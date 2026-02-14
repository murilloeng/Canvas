#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Colors/Color.hpp"
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Triangle : public Model3D
		{
		public:
			//constructors
			Triangle(void);

			//destructor
			~Triangle(void);

			//data
			Color color_fill(void) const;
			Color color_fill(const Color&);

			Color color_stroke(void) const;
			Color color_stroke(const Color&);

			vec3 position(uint32_t) const;
			vec3 position(uint32_t, const vec3&);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			vec3 m_positions[3];
			Color m_color_fill, m_color_stroke;
		};
	}
}