//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Point.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Point::Point(void) : m_color{0, 0, 0, 0}, m_position{0, 0, 0}
		{
			return;
		}

		//destructor
		Point::~Point(void)
		{
			return;
		}

		//data
		Color Point::color(void) const
		{
			return m_color;
		}
		Color Point::color(Color color)
		{
			return m_color = color;
		}

		vec3 Point::position(void) const
		{
			return m_position;
		}
		vec3 Point::position(vec3 position)
		{
			return m_position = position;
		}

		//type
		objects::type Point::type(void) const
		{
			return objects::type::point;
		}

		//buffers
		unsigned Point::vbo_size(void) const
		{
			return 1;
		}
		unsigned Point::ibo_size(unsigned index) const
		{
			return index == 0 ? 1 : 0;
		}

		//draw
		void Point::draw(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//ibo data
			ibo_data[0][m_ibo_index[0]] = m_vbo_index;
			//vbo data
			((vertices::Model*) vbo_data + m_vbo_index)->m_color = m_color;
			((vertices::Model*) vbo_data + m_vbo_index)->m_position = m_position;
		}
	}
}