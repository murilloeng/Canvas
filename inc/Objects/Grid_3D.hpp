#pragma once

//canvas
#include "inc/Objects/Group.hpp"

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
			unsigned mesh(unsigned) const;
			unsigned mesh(unsigned, unsigned);

			//type
			objects::type type(void) const override;

		private:
			//data
			unsigned m_mesh[3];
		};
	}
}