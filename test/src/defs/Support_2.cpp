//canvas
#include "inc/Objects/1D/Line.hpp"
#include "inc/Objects/2D/Triangle.hpp"

//examples
#include "inc/defs/Support_2.hpp"

//static data
static const unsigned nl = 5;

namespace examples
{
	//constructors
	Support_2::Support_2(float size) : m_size(size)
	{
		//objects
		m_objects.push_back(new canvas::objects::Triangle);
		for(unsigned i = 0; i <= nl; i++)
		{
			m_objects.push_back(new canvas::objects::Line);
		}
		//setup
		update_objects();
	}

	//destructor
	Support_2::~Support_2(void)
	{
		return;
	}

	//data
	float Support_2::size(void) const
	{
		return m_size;
	}
	float Support_2::size(float size)
	{
		m_size = size;
		update_objects();
		return m_size;
	}

	//update
	void Support_2::update_objects(void)
	{
		//cleanup
		color_fill("gray");
		color_stroke({0, 0, 0});
		//triangle
		const float a1 = 4 * M_PI / 3;
		const float a2 = 5 * M_PI / 3;
		((canvas::objects::Triangle*) m_objects[0])->point(0, {0, 0, 0});
		((canvas::objects::Triangle*) m_objects[0])->point(1, {m_size * cosf(a1), m_size * sinf(a1), 0});
		((canvas::objects::Triangle*) m_objects[0])->point(2, {m_size * cosf(a2), m_size * sinf(a2), 0});
		//lines
		for(unsigned i = 0; i <= nl; i++)
		{
			const float s = float(i) / nl;
			const float x2 = m_size * sinf(a1);
			const float x1 = m_size * cosf(a1) * (1 - 2 * s);
			((canvas::objects::Line*) m_objects[i + 1])->point(0, {x1, x2, 0});
			((canvas::objects::Line*) m_objects[i + 1])->point(1, {x1 - 0.2f / sqrtf(3) * m_size, x2 - 0.2f * m_size, 0});
		}
		
	}
}