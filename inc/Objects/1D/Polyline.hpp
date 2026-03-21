#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

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
			void draw(void) override;
			void setup(void) override;
			void update(void) override;

			//data
			std::vector<vec3> m_vertices;
		};
	}
}