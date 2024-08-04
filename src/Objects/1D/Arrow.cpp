//std
#include <cmath>

//canvas
#include "Canvas/inc/Objects/1D/Path.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Arrow::Arrow(void) : m_sense(true), m_width(0.1f), m_height(0.1f)
		{
			return;
		}

		//destructor
		Arrow::~Arrow(void)
		{
			return;
		}

		//data
		Path* Arrow::path(void) const
		{
			return m_path;
		}
		Path* Arrow::path(Path* path)
		{
			return m_path = path;
		}

		bool Arrow::sense(void) const
		{
			return m_sense;
		}
		bool Arrow::sense(bool sense)
		{
			return m_sense = sense;
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

		//data
		void Arrow::ibo_stroke_data(uint32_t** ibo_data) const
		{
			//data
			uint32_t* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//ibo data
			ibo_ptr[2 * 0 + 0] = m_vbo_index[0] + 0;
			ibo_ptr[2 * 0 + 1] = m_vbo_index[0] + 1;
			ibo_ptr[2 * 1 + 0] = m_vbo_index[0] + 0;
			ibo_ptr[2 * 1 + 1] = m_vbo_index[0] + 2;
			ibo_ptr[2 * 2 + 0] = m_vbo_index[0] + 0;
			ibo_ptr[2 * 2 + 1] = m_vbo_index[0] + 3;
			ibo_ptr[2 * 3 + 0] = m_vbo_index[0] + 0;
			ibo_ptr[2 * 3 + 1] = m_vbo_index[0] + 4;
		}
		void Arrow::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			const vec3 t2 = m_path->path_normal(m_parameter);
			const vec3 t3 = m_path->path_binormal(m_parameter);
			const vec3 xp = m_path->path_position(m_parameter);
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0];
			//vbo data
			const vec3 t1 = t2.cross(t3);
			(vbo_ptr + 0)->m_position = xp;
			(vbo_ptr + 1)->m_position = xp + (m_sense ? -1 : +1) * m_width * t1 - m_height * t2;
			(vbo_ptr + 2)->m_position = xp + (m_sense ? -1 : +1) * m_width * t1 + m_height * t2;
			(vbo_ptr + 3)->m_position = xp + (m_sense ? -1 : +1) * m_width * t1 - m_height * t3;
			(vbo_ptr + 4)->m_position = xp + (m_sense ? -1 : +1) * m_width * t1 + m_height * t3;
			for(uint32_t i = 0; i < 5; i++)
			{
				(vbo_ptr + i)->m_color = m_path->m_color_stroke;
			}
		}

		//buffers
		void Arrow::setup(void)
		{
			Object::setup();
			m_model_matrix = m_path->m_model_matrix;
			m_has_model_matrix = m_path->m_has_model_matrix;
		}
		void Arrow::buffers_size(void)
		{
			m_vbo_size[0] = 5 * m_stroke;
			m_ibo_size[1] = 8 * m_stroke;
		}
		void Arrow::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}