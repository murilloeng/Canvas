#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Line : public Object
		{
		public:
			//constructors
			Line(void);

			//destructor
			~Line(void);

			//data
			Color color(unsigned) const;
			Color color(unsigned, Color);

			vec3 position(unsigned) const;
			vec3 position(unsigned, vec3);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			Color m_colors[2];
			vec3 m_positions[2];
		};
	}
}