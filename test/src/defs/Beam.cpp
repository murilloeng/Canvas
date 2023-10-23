//canvas
#include "inc/Objects/1D/Arc.hpp"
#include "inc/Objects/1D/Line.hpp"
#include "inc/Objects/2D/Quad.hpp"

//examples
#include "inc/defs/Beam.hpp"

namespace examples
{
	//constructors
	Beam::Beam(float length, float height) : m_length(length), m_height(height)
	{
		//objects
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

	//update
	void Beam::update_objects(void)
	{
		//cleanup
		color_fill({0, 0, 1});
		color_stroke({0, 0, 0});
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
		((canvas::objects::Line*) m_objects[2])->point(0, {0, -m_height / 2, 0});
		((canvas::objects::Line*) m_objects[3])->point(0, {0, +m_height / 2, 0});
		((canvas::objects::Line*) m_objects[2])->point(1, {m_length, -m_height / 2, 0});
		((canvas::objects::Line*) m_objects[3])->point(1, {m_length, +m_height / 2, 0});
		//quad
		((canvas::objects::Quad*) m_objects[4])->stroke(false);
		((canvas::objects::Quad*) m_objects[4])->point(0, {0, -m_height / 2, 0});
		((canvas::objects::Quad*) m_objects[4])->point(3, {0, +m_height / 2, 0});
		((canvas::objects::Quad*) m_objects[4])->point(1, {m_length, -m_height / 2, 0});
		((canvas::objects::Quad*) m_objects[4])->point(2, {m_length, +m_height / 2, 0});
	}
}