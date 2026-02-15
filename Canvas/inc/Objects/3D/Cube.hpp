#pragma once

//canvas
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Cube : public Model3D
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