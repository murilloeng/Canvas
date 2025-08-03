//std
#include <cmath>

//canvas
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"

#include "Canvas/Canvas/inc/Objects/2D/Rectangle.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Rectangle::Rectangle(void) : 
			m_width{1.0f}, m_height{1.0f}, m_radius{0.1f}, m_directions{{1, 0, 0}, {0, 1, 0}}
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

		vec3 Rectangle::position(void) const
		{
			return m_position;
		}
		vec3 Rectangle::position(vec3 position)
		{
			return m_position = position;
		}

		vec3 Rectangle::direction(uint32_t index) const
		{
			return m_directions[index];
		}
		vec3 Rectangle::direction(uint32_t index, vec3 direction)
		{
			return m_directions[index] = direction;
		}

		uint32_t Rectangle::mesh(void)
		{
			return m_mesh;
		}
		uint32_t Rectangle::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		//vbos
		void Rectangle::vbo_fill_data(void) const
		{
			//data
			vertices::Model3D* vbo_ptr =  vbo_data_model_3D() + 4 * (m_mesh + 2) * m_stroke;
			//vbo data color
			for(uint32_t i = 0; i < 8 + 4 * m_mesh; i++)
			{
				vbo_ptr[i].m_color = m_color_fill;
			}
			//vbo data position
			vbo_position_data(vbo_ptr);
		}
		void Rectangle::vbo_stroke_data(void) const
		{
			//data
			vertices::Model3D* vbo_ptr =  vbo_data_model_3D();
			//vbo data color
			for(uint32_t i = 0; i < 8 + 4 * m_mesh; i++)
			{
				vbo_ptr[i].m_color = m_color_stroke;
			}
			//vbo data position
			vbo_position_data(vbo_ptr);
		}
		void Rectangle::vbo_position_data(vertices::Model3D* vbo_ptr) const
		{
			//data
			uint32_t index = 0;
			const float w = m_width;
			const float h = m_height;
			const float r = m_radius;
			const float p = float(M_PI_2);
			const vec3& t1 = m_directions[0];
			const vec3& t2 = m_directions[1];
			//vbo data
			vbo_ptr[index++].m_position = m_position + r * t1;
			vbo_ptr[index++].m_position = m_position + (w - r) * t1;
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				const float c2 = r;
				const float c1 = w - r;
				const float t = p * (i + 1) / (m_mesh + 1) - p;
				vbo_ptr[index++].m_position = m_position + (c1 + r * cosf(t)) * t1 + (c2 + r * sinf(t)) * t2;
			}
			vbo_ptr[index++].m_position = m_position + w * t1 + r * t2;
			vbo_ptr[index++].m_position = m_position + w * t1 + (h - r) * t2;
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				const float c1 = w - r;
				const float c2 = h - r;
				const float t = p * (i + 1) / (m_mesh + 1);
				vbo_ptr[index++].m_position = m_position + (c1 + r * cosf(t)) * t1 + (c2 + r * sinf(t)) * t2;
			}
			vbo_ptr[index++].m_position = m_position + (w - r) * t1 + h * t2;
			vbo_ptr[index++].m_position = m_position + r * t1 + h * t2;
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				const float c1 = r;
				const float c2 = h - r;
				const float t = p * (i + 1) / (m_mesh + 1) + p;
				vbo_ptr[index++].m_position = m_position + (c1 + r * cosf(t)) * t1 + (c2 + r * sinf(t)) * t2;
			}
			vbo_ptr[index++].m_position = m_position + (h - r) * t2;
			vbo_ptr[index++].m_position = m_position + r * t2;
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				const float c1 = r;
				const float c2 = r;
				const float t = p * (i + 1) / (m_mesh + 1) + 2 * p;
				vbo_ptr[index++].m_position = m_position + (c1 + r * cosf(t)) * t1 + (c2 + r * sinf(t)) * t2;
			}
		}

		//ibos
		void Rectangle::ibo_fill_data(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(2);
			const uint32_t nt = 4 * m_mesh + 6;
			const uint32_t nv = 4 * m_mesh + 8;
			//ibo data
			for(uint32_t i = 0; i < nt; i++)
			{
				ibo_ptr[3 * i + 0] = m_vbo_index[0] + nv * m_stroke;
				ibo_ptr[3 * i + 1] = m_vbo_index[0] + nv * m_stroke + (i + 1) % nv;
				ibo_ptr[3 * i + 2] = m_vbo_index[0] + nv * m_stroke + (i + 2) % nv;
			}
		}
		void Rectangle::ibo_stroke_data(void) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data(1);
			const uint32_t nv = 4 * (m_mesh + 2);
			//ibo data
			for(uint32_t i = 0; i < nv; i++)
			{
				ibo_ptr[2 * i + 0] = m_vbo_index[0] + (i + 0) % nv;
				ibo_ptr[2 * i + 1] = m_vbo_index[0] + (i + 1) % nv;
			}
		}

		//buffers
		void Rectangle::buffers_size(void)
		{
			m_ibo_size[1] = 8 * (m_mesh + 2) * m_stroke;
			m_ibo_size[2] = 6 * (2 * m_mesh + 3) * m_fill;
			m_vbo_size[0] = 4 * (m_mesh + 2) * (m_fill + m_stroke);
		}
		void Rectangle::buffers_data(void) const
		{
			if(m_fill) vbo_fill_data();
			if(m_fill) ibo_fill_data();
			if(m_stroke) vbo_stroke_data();
			if(m_stroke) ibo_stroke_data();
		}

		//static
		uint32_t Rectangle::m_mesh = 20;
	}
}