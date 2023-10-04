//canvas
#include "inc/Objects/Arc.hpp"
#include "inc/Objects/Quad.hpp"
#include "inc/Objects/Line.hpp"
#include "inc/Objects/Type.hpp"
#include "inc/Examples/defs/Beam.hpp"

namespace examples
{
	//constructors
	Beam::Beam(float length, float height) : m_length(length), m_height(height)
	{
		//objects
		m_fill_colors.resize(1);
		m_stroke_colors.resize(1);
		m_objects.push_back(new canvas::objects::Arc);
		m_objects.push_back(new canvas::objects::Arc);
		m_objects.push_back(new canvas::objects::Line);
		m_objects.push_back(new canvas::objects::Line);
		m_objects.push_back(new canvas::objects::Quad);
		//setup
		update_objects();
	}

	//destructor
	Beam::~Beam(void)
	{
		return;
	}

	//data
	float Beam::height(void) const
	{
		return m_height;
	}
	float Beam::height(float height)
	{
		m_height = height;
		update_objects();
		return m_height;
	}

	float Beam::length(void) const
	{
		return m_length;
	}
	float Beam::length(float length)
	{
		m_length = length;
		update_objects();
		return m_length;
	}

	//type
	canvas::objects::type Beam::type(void) const
	{
		return canvas::objects::type::user;
	}

	//update
	void Beam::update_objects(void)
	{
		//cleanup
		fill_color({0, 0, 1});
		stroke_color({0, 0, 0});
		for(canvas::objects::Object* object : m_objects)
		{
			object->affine(canvas::mat4());
		}
		//arcs
		((canvas::objects::Arc*) m_objects[0])->angle(1, M_PI);
		((canvas::objects::Arc*) m_objects[1])->angle(1, M_PI);
		((canvas::objects::Arc*) m_objects[0])->radius(m_height / 2);
		((canvas::objects::Arc*) m_objects[1])->radius(m_height / 2);
		((canvas::objects::Arc*) m_objects[0])->rotate({0, 0, +M_PI_2});
		((canvas::objects::Arc*) m_objects[1])->rotate({0, 0, -M_PI_2});
		((canvas::objects::Arc*) m_objects[1])->shift({m_length, 0, 0});
		//lines
		((canvas::objects::Line*) m_objects[2])->position(0, {0, -m_height / 2, 0});
		((canvas::objects::Line*) m_objects[3])->position(0, {0, +m_height / 2, 0});
		((canvas::objects::Line*) m_objects[2])->position(1, {m_length, -m_height / 2, 0});
		((canvas::objects::Line*) m_objects[3])->position(1, {m_length, +m_height / 2, 0});
		//quad
		((canvas::objects::Quad*) m_objects[4])->stroke(false);
		((canvas::objects::Quad*) m_objects[4])->position(0, {0, -m_height / 2, 0});
		((canvas::objects::Quad*) m_objects[4])->position(3, {0, +m_height / 2, 0});
		((canvas::objects::Quad*) m_objects[4])->position(1, {m_length, -m_height / 2, 0});
		((canvas::objects::Quad*) m_objects[4])->position(2, {m_length, +m_height / 2, 0});
	}
}