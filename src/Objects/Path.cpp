//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Path.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Path::Path(void)
		{
			return;
		}

		//destructor
		Path::~Path(void)
		{
			return;
		}

		//data
		void Path::add_point(const vec3& point)
		{
			m_points.push_back(point);
		}
		const std::vector<vec3>& Path::points(void) const
		{
			return m_points;
		}

		//type
		objects::type Path::type(void) const
		{
			return objects::type::path;
		}

		//buffers
		unsigned Path::vbo_size(void) const
		{
			return m_points.size() * m_stroke;
		}
		unsigned Path::ibo_size(unsigned index) const
		{
			return (m_points.size() - 1) * (index == 1) * m_stroke;
		}

		//draw
		void Path::ibo_fill_data(unsigned** ibo_data) const
		{
			return;
		}
		void Path::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
			//ibo data
			for(unsigned i = 0; i + 1 < m_points.size(); i++)
			{
				ibo_ptr[2 * i + 0] = m_vbo_index + i + 0;
				ibo_ptr[2 * i + 1] = m_vbo_index + i + 1;
			}
		}
		void Path::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			return;
		}
		void Path::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
			//vbo data
			for(unsigned i = 0; i < m_points.size(); i++)
			{
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = m_points[i];
			}
		}
		void Path::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
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