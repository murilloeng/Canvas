#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Circle : public BaseModel3D
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
			void draw(void) override;
			void setup(void) override;
			void update(void) override;

			//data
			static uint32_t m_mesh;
		};
	}
}