//canvas
#include "inc/Objects/Quad.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Examples/defs/Support_3.hpp"

namespace examples
{
	//constructors
	Support_3::Support_3(float size_1, float size_2) : m_size{size_1, size_2}
	{
		//objects
		m_fill_colors.resize(1);
		m_stroke_colors.resize(1);
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

	//type
	canvas::objects::type Support_3::type(void) const
	{
		return canvas::objects::type::user;
	}

	//update
	void Support_3::update_objects(void)
	{
		//cleanup
		fill_color("gray");
		stroke_color({0, 0, 0});
		//objects
		((canvas::objects::Quad*) m_objects[0])->position(0, {0, -m_size[0] / 2, 0});
		((canvas::objects::Quad*) m_objects[0])->position(1, {0, +m_size[0] / 2, 0});
		((canvas::objects::Quad*) m_objects[0])->position(2, {-m_size[1], +m_size[0] / 2, 0});
		((canvas::objects::Quad*) m_objects[0])->position(3, {-m_size[1], -m_size[0] / 2, 0});
	}
}