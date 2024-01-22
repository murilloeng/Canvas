//std
#include <cmath>

//canvas
#include "Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/inc/Objects/2D/Triangle.hpp"

//examples
#include "Canvas/Test/inc/defs/Support_1.hpp"

namespace examples
{
	//constructors
	Support_1::Support_1(float size) : m_size(size)
	{
		//objects
		m_geometries.push_back(new canvas::objects::Line);
		m_geometries.push_back(new canvas::objects::Triangle);
		//setup
		update_objects();
	}

	//destructor
	Support_1::~Support_1(void)
	{
		return;
	}

	//data
	float Support_1::size(void) const
	{
		return m_size;
	}
	float Support_1::size(float size)
	{
		m_size = size;
		update_objects();
		return m_size;
	}

	//update
	void Support_1::update_objects(void)
	{
		//cleanup
		color_fill("gray");
		color_stroke({0, 0, 0});
		//triangle
		const float a1 = 4 * float(M_PI) / 3;
		const float a2 = 5 * float(M_PI) / 3;
		((canvas::objects::Triangle*) m_geometries[1])->point(0, {0, 0, 0});
		((canvas::objects::Triangle*) m_geometries[1])->point(1, {m_size * cosf(a1), m_size * sinf(a1), 0});
		((canvas::objects::Triangle*) m_geometries[1])->point(2, {m_size * cosf(a2), m_size * sinf(a2), 0});
		//lines
		((canvas::objects::Line*) m_geometries[0])->point(0, {m_size * cosf(a1), m_size * sinf(a1) - 0.2f * m_size, 0});
		((canvas::objects::Line*) m_geometries[0])->point(1, {m_size * cosf(a2), m_size * sinf(a2) - 0.2f * m_size, 0});
	}
}