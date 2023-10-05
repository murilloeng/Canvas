//canvas
#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Line.hpp"
#include "inc/Objects/Surfaces/Triangle.hpp"

#include "inc/Examples/defs/Support_1.hpp"

namespace examples
{
	//constructors
	Support_1::Support_1(float size) : m_size(size)
	{
		//objects
		m_fill_colors.resize(1);
		m_stroke_colors.resize(1);
		m_objects.push_back(new canvas::objects::Line);
		m_objects.push_back(new canvas::objects::Triangle);
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

	//type
	canvas::objects::type Support_1::type(void) const
	{
		return canvas::objects::type::user;
	}

	//update
	void Support_1::update_objects(void)
	{
		//cleanup
		fill_color("gray");
		stroke_color({0, 0, 0});
		//triangle
		const float a1 = 4 * M_PI / 3;
		const float a2 = 5 * M_PI / 3;
		((canvas::objects::Triangle*) m_objects[1])->point(0, {0, 0, 0});
		((canvas::objects::Triangle*) m_objects[1])->point(1, {m_size * cosf(a1), m_size * sinf(a1), 0});
		((canvas::objects::Triangle*) m_objects[1])->point(2, {m_size * cosf(a2), m_size * sinf(a2), 0});
		//lines
		((canvas::objects::Line*) m_objects[0])->point(0, {m_size * cosf(a1), m_size * sinf(a1) - 0.2f * m_size, 0});
		((canvas::objects::Line*) m_objects[0])->point(1, {m_size * cosf(a2), m_size * sinf(a2) - 0.2f * m_size, 0});
	}
}