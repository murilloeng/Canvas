#pragma once

//canvas
#include "Canvas/inc/Objects/Group.hpp"

namespace canvas
{
	namespace objects
	{
		class Grid_3D : public Group
		{
		public:
			//constructors
			Grid_3D(void);

			//destructor
			~Grid_3D(void);

			//data
			uint32_t mesh(uint32_t) const;
			uint32_t mesh(uint32_t, uint32_t);

		protected:
			//data
			uint32_t m_mesh[3];
		};
	}
}