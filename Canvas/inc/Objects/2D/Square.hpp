#pragma once

//canvas
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Square : public Model3D
		{
		public:
			//constructors
			Square(void);

			//destructor
			~Square(void);

		private:
			//draw
			void setup(void) override;
			void draw(void) const override;
		};
	}
}