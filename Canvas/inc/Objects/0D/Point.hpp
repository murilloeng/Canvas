#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Point : public Geometry
		{
		public:
			//constructors
			Point(void);

			//destructor
			~Point(void);

			//data
			vec3 position(void) const;
			vec3 position(const vec3&);

		protected:
			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			vec3 m_position;
		};
	}
}