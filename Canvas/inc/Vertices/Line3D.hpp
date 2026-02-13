#pragma once

//canvas
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace vertices
	{
		class Line3D : public Model3D
		{
		public:
			//constructor
			Line3D(void);

			//destructor
			~Line3D(void);

			//print
			void print(void) const;

			//data
			float m_thickness;
		};
	}
}