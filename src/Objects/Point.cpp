//std
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

		const float* Point::position(void) const
		{
			return m_position;
		}
		const float* Point::position(const float* position)
		{
			return this->position(position[0], position[1], position[2]);
		}
		const float* Point::position(float x1, float x2, float x3)
		{
			m_position[0] = x1;
			m_position[1] = x2;
			m_position[2] = x3;
			return m_position;
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
			memcpy(((vertices::Model*) vbo_data + m_vbo_index)->m_position, m_position, 3 * sizeof(float));
		}
	}
}