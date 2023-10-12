#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Polygon : public Object
		{
		public:
			//constructors
			Polygon(void);

			//destructor
			~Polygon(void);

			//data
			vec3 position(unsigned) const;
			vec3 position(unsigned, const vec3&);

		private:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_positions[2];
		};
	}
}