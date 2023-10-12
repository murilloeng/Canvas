#pragma once

//canvas
#include "inc/Math/vec3.hpp"
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
			vec3 position(void) const;
			vec3 position(const vec3&);

		private:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_position;
		};
	}
}