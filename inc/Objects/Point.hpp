#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Point : public Object
		{
		public:
			//constructors
			Point(void);

			//destructor
			~Point(void);

			//data
			Color color(Color);
			Color color(void) const;

			vec3 position(vec3);
			vec3 position(void) const;

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			Color m_color;
			vec3 m_position;
		};
	}
}