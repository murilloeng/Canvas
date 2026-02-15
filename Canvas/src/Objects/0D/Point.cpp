//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Objects/0D/Point.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Point::Point(void) : m_position{0, 0, 0}
		{
			m_vbo.allocate(1);
		}

		//destructor
		Point::~Point(void)
		{
			return;
		}

		//data
		vec3 Point::position(void) const
		{
			return m_position;
		}
		vec3 Point::position(const vec3& position)
		{
			return m_position = position;
		}

		//draw
		void Point::setup(void)
		{
			//data
			vertices::Model3D* vertex = (vertices::Model3D*) m_vbo.data();
			//vbo data
			vertex->m_color = m_color_fill;
			vertex->m_position = m_position;
			//vbo transfer
			m_vbo.transfer();
		}
		void Point::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}
}