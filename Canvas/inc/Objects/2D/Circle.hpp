#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Colors/Color.hpp"
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

			Color color_fill(void) const;
			Color color_fill(const Color&);

			Color color_stroke(void) const;
			Color color_stroke(const Color&);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Color m_color_fill;
			Color m_color_stroke;
			static uint32_t m_mesh;
		};
	}
}