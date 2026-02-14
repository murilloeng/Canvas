#pragma once

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"
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

			//data
			Color color_fill(void) const;
			Color color_fill(const Color&);

			Color color_stroke(void) const;
			Color color_stroke(const Color&);

		private:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Color m_color_fill;
			Color m_color_stroke;
		};
	}
}