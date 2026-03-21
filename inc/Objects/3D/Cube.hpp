#pragma once

//canvas
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Cube : public BaseModel3D
		{
		public:
			//constructors
			Cube(void);

			//destructor
			~Cube(void);

		private:
			//draw
			void setup(void) override;
			void draw(void) const override;
		};
	}
}