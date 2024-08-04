//std
#include <cmath>

//canvas
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/1D/Path.hpp"
#include "Canvas/inc/Objects/1D/Arrow.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Path::Path(void) : m_mesh(40)
		{
			return;
		}

		//destructor
		Path::~Path(void)
		{
			return;
		}

		//data
		uint32_t Path::mesh(void) const
		{
			return m_mesh;
		}
		uint32_t Path::mesh(uint32_t mesh)
		{
			return m_mesh = mesh;
		}

		//path
		float Path::path_max(void) const
		{
			return 1.0f;
		}
		vec3 Path::path_normal(float s) const
		{
			//path
			const vec3 h = path_hessian(s);
			const vec3 g = path_gradient(s);
			//normal
			if(h.cross(g).norm() != 0)
			{
				const vec3 t = g.unit();
				return (h - h.inner(t) * t).unit();
			}
			else
			{
				vec3 t2, t3;
				g.unit().triad(t2, t3);
				return t2;
			}
		}
		vec3 Path::path_tangent(float s) const
		{
			return path_gradient(s).unit();
		}
		vec3 Path::path_binormal(float s) const
		{
			return path_tangent(s).cross(path_normal(s));
		}

		//data
		void Path::ibo_stroke_data(uint32_t** ibo_data) const
		{
			//data
			uint32_t vbo_index = m_vbo_index[0] + m_vbo_size[0] - m_mesh - 1;
			uint32_t* ibo_ptr = ibo_data[1] + m_ibo_index[1] + m_ibo_size[1] - 2 * m_mesh;
			//ibo data
			for(uint32_t i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + i + 0;
				ibo_ptr[2 * i + 1] = vbo_index + i + 1;
			}
		}
		void Path::vbo_stroke_data(vertices::Vertex** vbo_data) const
		{
			//data
			uint32_t vbo_index = m_vbo_index[0] + m_vbo_size[0] - m_mesh - 1;
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + vbo_index;
			//vbo data
			for(uint32_t i = 0; i <= m_mesh; i++)
			{
				const float s = i * path_max() / m_mesh;
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = path_position(s);
			}
		}

		//buffers
		void Path::buffers_size(void)
		{
			m_ibo_size[1] = 2 * m_mesh * m_stroke;
			m_vbo_size[0] = (m_mesh + 1) * m_stroke;
		}
		void Path::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}