#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Line : public BaseModel3D
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
			void draw(void) override;
			void update(void) override;

			//data
			vec3 m_positions[2];
		};
	}
}