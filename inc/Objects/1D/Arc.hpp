#pragma once

#include <cstdint>

//canvas
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Arc : public BaseModel3D
		{
		public:
			//constructors
			Arc(void);

			//destructor
			~Arc(void);

			//data
			float angle(float);
			float angle(void) const;

			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		protected:
			//draw
			void draw(void) override;
			void setup(void) override;
			void update(void) override;

			//data
			float m_angle;
			static uint32_t m_mesh;
		};
	}
}