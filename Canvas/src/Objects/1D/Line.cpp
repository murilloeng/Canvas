//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Objects/1D/Line.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Line::Line(void) : m_positions{{0, 0, 0}, {1, 0, 0}}
		{
			m_vbo.allocate(2);
		}

		//destructor
		Line::~Line(void)
		{
			return;
		}

		//data
		vec3 Line::position(uint32_t index) const
		{
			return m_positions[index];
		}
		vec3 Line::position(uint32_t index, const vec3& point)
		{
			return m_positions[index] = point;
		}

		//draw
		void Line::setup(void)
		{
			//data
			vertices::Model3D* vbo_data = (vertices::Model3D*) m_vbo.data();
			//colors
			vbo_data[0].m_color = m_color_stroke;
			vbo_data[1].m_color = m_color_stroke;
			//positions
			vbo_data[0].m_position = m_positions[0];
			vbo_data[1].m_position = m_positions[1];
			//transfer
			m_vbo.transfer();
		}
		void Line::draw(void) const
		{
			m_vao.bind();
			m_shader.bind();
			glDrawArrays(GL_LINES, 0, 2);
		}
	}
}