#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Circle : public Model3D
		{
		public:
			//constructors
			Circle(void);

			//destructor
			~Circle(void);

			//data
			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			static uint32_t m_mesh;
		};
	}
}