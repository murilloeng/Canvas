//std
#include <cmath>
#include <cstdio>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/2D/Grid_2D.hpp"
#include "inc/Objects/2D/Grid_3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Grid_3D::Grid_3D(void) : m_mesh{10, 10, 10}
		{
			//setup
			m_objects.push_back(new Grid_2D);
			m_objects.push_back(new Grid_2D);
			m_objects.push_back(new Grid_2D);
			//affines
			m_objects[0]->shift({-1, 0, 0});
			m_objects[1]->shift({0, -1, 0});
			m_objects[2]->shift({0, 0, -1});
			m_objects[0]->rotate({0, M_PI_2, 0}, false);
			m_objects[1]->rotate({0, 0, M_PI_2}, false);
			m_objects[1]->rotate({0, -M_PI_2, 0}, false);
		}

		//destructor
		Grid_3D::~Grid_3D(void)
		{
			return;
		}

		//data
		unsigned Grid_3D::mesh(unsigned index) const
		{
			return m_mesh[index];
		}
		unsigned Grid_3D::mesh(unsigned index, unsigned mesh)
		{
			((Grid_2D*) m_objects[(index + 0) % 3])->mesh(0, mesh);
			((Grid_2D*) m_objects[(index + 2) % 3])->mesh(1, mesh);
			return m_mesh[index] = mesh;
		}
	}
}