//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Arrow.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Arrow::Arrow(void) : m_sense(true), m_point{0, 0, 0}, m_width(0), m_height(0), m_directions{{0, 1, 0}, {0, 0, 1}}
		{
			return;
		}

		//destructor
		Arrow::~Arrow(void)
		{
			return;
		}

		//data
		bool Arrow::sense(void) const
		{
			return m_sense;
		}
		bool Arrow::sense(bool sense)
		{
			return m_sense = sense;
		}

		vec3 Arrow::point(void) const
		{
			return m_point;
		}
		vec3 Arrow::point(const vec3& point)
		{
			return m_point = point;
		}

		float Arrow::width(void) const
		{
			return m_width;
		}
		float Arrow::width(float width)
		{
			return m_width = width;
		}

		float Arrow::height(void) const
		{
			return m_height;
		}
		float Arrow::height(float height)
		{
			return m_height = height;
		}

		float Arrow::parameter(void) const
		{
			return m_parameter;
		}
		float Arrow::parameter(float parameter)
		{
			return m_parameter = parameter;
		}

		vec3 Arrow::direction(unsigned index) const
		{
			return m_directions[index];
		}
		vec3 Arrow::direction(unsigned index, const vec3& direction)
		{
			return m_directions[index] = direction;
		}

		//type
		objects::type Arrow::type(void) const
		{
			return objects::type::arrow;
		}

		//buffers
		unsigned Arrow::vbo_size(void) const
		{
			return 5 * m_stroke;
		}
		unsigned Arrow::ibo_size(unsigned index) const
		{
			return 4 * (index == 1);
		}

		//draw
		void Arrow::ibo_fill_data(unsigned** ibo_data) const
		{
			return;
		}
		void Arrow::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//ibo data
			ibo_ptr[2 * 0 + 0] = m_vbo_index + 0;
			ibo_ptr[2 * 0 + 1] = m_vbo_index + 1;
			ibo_ptr[2 * 1 + 0] = m_vbo_index + 0;
			ibo_ptr[2 * 1 + 1] = m_vbo_index + 2;
			ibo_ptr[2 * 2 + 0] = m_vbo_index + 0;
			ibo_ptr[2 * 2 + 1] = m_vbo_index + 3;
			ibo_ptr[2 * 3 + 0] = m_vbo_index + 0;
			ibo_ptr[2 * 3 + 1] = m_vbo_index + 4;
		}
		void Arrow::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			return;
		}
		void Arrow::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			const vec3 t2 = m_directions[0];
			const vec3 t3 = m_directions[1];
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			const vec3 t1 = t2.cross(t3);
			(vbo_ptr + 0)->m_position = m_point;
			(vbo_ptr + 1)->m_position = m_point + (m_sense ? -1 : +1) * m_width * t1 - m_height * t2;
			(vbo_ptr + 2)->m_position = m_point + (m_sense ? -1 : +1) * m_width * t1 + m_height * t2;
			(vbo_ptr + 3)->m_position = m_point + (m_sense ? -1 : +1) * m_width * t1 - m_height * t3;
			(vbo_ptr + 4)->m_position = m_point + (m_sense ? -1 : +1) * m_width * t1 + m_height * t3;
			for(unsigned i = 0; i < 5; i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
			}
		}
		void Arrow::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			//ibo data
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}