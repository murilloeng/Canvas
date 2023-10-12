//canvas
#include "inc/Objects/2D/Quad.hpp"

#include "inc/Examples/defs/Support_3.hpp"

namespace examples
{
	//constructors
	Support_3::Support_3(float size_1, float size_2) : m_size{size_1, size_2}
	{
		//objects
		m_objects.push_back(new canvas::objects::Quad);
		//setup
		update_objects();
	}

	//destructor
	Support_3::~Support_3(void)
	{
		return;
	}

	//data
	float Support_3::size(unsigned index) const
	{
		return m_size[index];
	}
	float Support_3::size(unsigned index, float size)
	{
		m_size[index] = size;
		update_objects();
		return m_size[index];
	}

	//update
	void Support_3::update_objects(void)
	{
		//cleanup
		color_fill("gray");
		color_stroke({0, 0, 0});
		//objects
		((canvas::objects::Quad*) m_objects[0])->point(0, {0, -m_size[0] / 2, 0});
		((canvas::objects::Quad*) m_objects[0])->point(1, {0, +m_size[0] / 2, 0});
		((canvas::objects::Quad*) m_objects[0])->point(2, {-m_size[1], +m_size[0] / 2, 0});
		((canvas::objects::Quad*) m_objects[0])->point(3, {-m_size[1], -m_size[0] / 2, 0});
	}
}