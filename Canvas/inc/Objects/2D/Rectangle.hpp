#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec2.hpp"

#include "Canvas/Canvas/inc/Colors/Color.hpp"

#include "Canvas/Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Rectangle : public Geometry
		{
		public:
			//constructor
			Rectangle(void);

			//destructor
			~Rectangle(void);

			//data
			float width(float);
			float width(void) const;

			float height(float);
			float height(void) const;

			float radius(float);
			float radius(void) const;

			vec2 position(vec2);
			vec2 position(void) const;

			Color color_fill(Color);
			Color color_fill(void) const;

			Color color_stroke(Color);
			Color color_stroke(void) const;

			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		private:
			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			float m_width;
			float m_height;
			float m_radius;
			vec2 m_position;
			Color m_color_fill;
			Color m_color_stroke;
			static uint32_t m_mesh;
		};
	}
}