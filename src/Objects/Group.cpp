//canvas
#include "inc/Objects/Group.hpp"
#include "inc/Vertices/Model.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Group::Group(void)
		{
			return;
		}

		//destructor
		Group::~Group(void)
		{
			for(const Object* object : m_objects)
			{
				delete object;
			}
		}

		//data
		bool Group::dot(bool dot)
		{
			for(Object* object : m_objects)
			{
				object->dot(dot);
			}
			return m_dot = dot;
		}
		bool Group::fill(bool fill)
		{
			for(Object* object : m_objects)
			{
				object->fill(fill);
			}
			return m_fill = fill;
		}
		bool Group::stroke(bool stroke)
		{
			for(Object* object : m_objects)
			{
				object->stroke(stroke);
			}
			return m_stroke = stroke;
		}

		void Group::dot_color(const Color& dot_color)
		{
			for(Object* object : m_objects)
			{
				object->dot_color(dot_color);
			}
			Object::dot_color(dot_color);
		}
		void Group::dot_color(const Color& dot_color, unsigned index)
		{
			for(Object* object : m_objects)
			{
				object->dot_color(dot_color, index);
			}
			Object::dot_color(dot_color, index);
		}

		void Group::fill_color(const Color& fill_color)
		{
			for(Object* object : m_objects)
			{
				object->fill_color(fill_color);
			}
			Object::fill_color(fill_color);
		}
		void Group::fill_color(const Color& fill_color, unsigned index)
		{
			for(Object* object : m_objects)
			{
				object->fill_color(fill_color, index);
			}
			Object::fill_color(fill_color, index);
		}

		void Group::stroke_color(const Color& stroke_color)
		{
			for(Object* object : m_objects)
			{
				object->stroke_color(stroke_color);
			}
			Object::stroke_color(stroke_color);
		}
		void Group::stroke_color(const Color& stroke_color, unsigned index)
		{
			for(Object* object : m_objects)
			{
				object->stroke_color(stroke_color, index);
			}
			Object::stroke_color(stroke_color, index);
		}

		//buffers
		unsigned Group::vbo_size(void) const
		{
			unsigned s = 0;
			for(const Object* object : m_objects)
			{
				s += object->vbo_size();
			}
			return s;
		}
		unsigned Group::ibo_size(unsigned index) const
		{
			unsigned s = 0;
			for(const Object* object : m_objects)
			{
				s += object->ibo_size(index);
			}
			return s;
		}

		//draw
		void Group::vbo_affine(vertices::Vertex* vbo_data) const
		{
			//data
			unsigned vbo_index = m_vbo_index;
			//affine
			for(const Object* object : m_objects)
			{
				for(unsigned i = 0; i < object->vbo_size(); i++)
				{
					((vertices::Model*) vbo_data + vbo_index + i)->m_position *= object->affine();
				}
				vbo_index += object->vbo_size();
			}
		}
		void Group::buffers_index(unsigned& vbo_counter, unsigned ibo_counter[])
		{
			//data
			unsigned vbo_group_counter = vbo_counter;
			unsigned ibo_group_index[] = {ibo_counter[0], ibo_counter[1], ibo_counter[2]};
			//indexes
			for(Object* object : m_objects)
			{
				object->buffers_index(vbo_group_counter, ibo_group_index);
			}
			Object::buffers_index(vbo_counter, ibo_counter);
		}
		void Group::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			for(const Object* object : m_objects)
			{
				object->buffers_data(vbo_data, ibo_data);
			}
			vbo_affine(vbo_data);
		}
	}
}