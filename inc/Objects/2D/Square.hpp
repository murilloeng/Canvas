#pragma once

//canvas
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Square : public BaseModel3D
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