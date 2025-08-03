//canvas
#include "Canvas/Canvas/inc/Objects/2D/Rectangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Rectangle::Rectangle(void) : 
			m_width{1.0f}, m_height{1.0f}, m_radius{0.1f}
		{
			return;
		}
		
		//destructor
		Rectangle::~Rectangle(void)
		{
			return;
		}

		//data
		float Rectangle::width(void) const
		{
			return m_width;
		}
		float Rectangle::width(float width)
		{
			return m_width = width;
		}

		float Rectangle::height(void) const
		{
			return m_height;
		}
		float Rectangle::height(float height)
		{
			return m_height = height;
		}

		float Rectangle::radius(void) const
		{
			return m_radius;
		}
		float Rectangle::radius(float radius)
		{
			return m_radius = radius;
		}

		vec2 Rectangle::position(void) const
		{
			return m_position;
		}
		vec2 Rectangle::position(vec2 position)
		{
			return m_position = position;
		}

		Color Rectangle::color_fill(void) const
		{
			return m_color_fill;
		}
		Color Rectangle::color_fill(Color color_fill)
		{
			return m_color_fill = color_fill;
		}

		Color Rectangle::color_stroke(void) const
		{
			return m_color_stroke;
		}
		Color Rectangle::color_stroke(Color color_stroke)
		{
			return m_color_stroke = color_stroke;
		}

		uint32_t Rectangle::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Rectangle::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		//buffers
		void Rectangle::buffers_size(void)
		{
			m_ibo_size[8] = (6 + 4 * m_mesh) * m_fill;
			m_ibo_size[7] = 8 * (m_mesh + 2) * m_stroke;
			m_vbo_size[3] = (8 + 4 * m_mesh) * (m_fill + m_stroke);
		}
		void Rectangle::buffers_data(void) const
		{

		}

		//static
		uint32_t Rectangle::m_mesh = 20;
	}
}