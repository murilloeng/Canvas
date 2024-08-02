//std
#include <cmath>
#include <cstdio>

//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"

#include "Canvas/inc/Objects/2D/Grid_2D.hpp"
#include "Canvas/inc/Objects/2D/Grid_3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Grid_3D::Grid_3D(void) : m_mesh{10, 10, 10}
		{
			//setup
			m_geometries.push_back(new Grid_2D);
			m_geometries.push_back(new Grid_2D);
			m_geometries.push_back(new Grid_2D);
			//affines
			m_geometries[0]->shift({-1, 0, 0});
			m_geometries[1]->shift({0, -1, 0});
			m_geometries[2]->shift({0, 0, -1});
			m_geometries[0]->rotate({0, float(M_PI_2), 0}, false);
			m_geometries[1]->rotate({0, 0, float(M_PI_2)}, false);
			m_geometries[1]->rotate({0, -float(M_PI_2), 0}, false);
		}

		//destructor
		Grid_3D::~Grid_3D(void)
		{
			return;
		}

		//data
		uint32_t Grid_3D::mesh(uint32_t index) const
		{
			return m_mesh[index];
		}
		uint32_t Grid_3D::mesh(uint32_t index, uint32_t mesh)
		{
			((Grid_2D*) m_geometries[(index + 0) % 3])->mesh(0, mesh);
			((Grid_2D*) m_geometries[(index + 2) % 3])->mesh(1, mesh);
			return m_mesh[index] = mesh;
		}
	}
}