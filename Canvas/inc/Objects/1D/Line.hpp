#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Line : public Model3D
		{
		public:
			//constructors
			Line(void);

			//destructor
			~Line(void);

			//data
			vec3 position(uint32_t) const;
			vec3 position(uint32_t, const vec3&);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			vec3 m_positions[2];
		};
	}
}