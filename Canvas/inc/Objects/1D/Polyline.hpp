#pragma once

//std
#include <vector>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Polyline : public BaseModel3D
		{
		public:
			//constructors
			Polyline(void);

			//destructor
			~Polyline(void);

			//data
			std::vector<vec3>& vertices(void);
			const std::vector<vec3>& vertices(void) const;

		protected:
			//buffers
			void setup(void) override;
			void draw(void) const override;

			//data
			std::vector<vec3> m_vertices;
		};
	}
}