#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Point : public Model3D
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
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			vec3 m_position;
		};
	}
}