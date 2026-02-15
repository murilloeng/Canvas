#pragma once

#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Arc : public Model3D
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
			void setup(void) override;
			void draw(void) const override;

			//data
			float m_angle;
			static uint32_t m_mesh;
		};
	}
}