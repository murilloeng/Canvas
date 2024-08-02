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

		//arrows
		void Path::add_arrow(float s, bool sense)
		{
			//data
			Arrow* arrow = new Arrow;
			//arrow
			arrow->parameter(s);
			arrow->sense(sense);
			m_geometries.push_back(arrow);
		}
		void Path::remove_arrow(uint32_t index)
		{
			uint32_t counter = 0;
			for(uint32_t i = 0; i < m_geometries.size(); i++)
			{
				if(dynamic_cast<const Arrow*>(m_geometries[i]))
				{
					if(counter == index)
					{
						delete m_geometries[i];
						m_geometries.erase(m_geometries.begin() + i);
					}
					counter++;
				}
			}
		}
		uint32_t Path::arrows(void) const
		{
			uint32_t counter = 0;
			for(const Object* object : m_geometries)
			{
				if(dynamic_cast<const Arrow*>(object))
				{
					counter++;
				}
			}
			return counter;
		}
		Arrow* Path::arrow(uint32_t index) const
		{
			uint32_t counter = 0;
			for(Geometry* geometry : m_geometries)
			{
				if(dynamic_cast<Arrow*>(geometry))
				{
					if(counter != index)
					{
						counter++;
					}
					else
					{
						return (Arrow*) geometry;
					}
				}
			}
			return nullptr;
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

		//sizes
		uint32_t Path::vbo_size(uint32_t index) const
		{
			return Group::vbo_size(index) + (m_mesh + 1) * m_stroke * (index == 0);
		}
		uint32_t Path::ibo_size(uint32_t index) const
		{
			return Group::ibo_size(index) + 2 * m_mesh * (index == 1) * m_stroke;
		}

		//buffers
		void Path::ibo_stroke_data(uint32_t** ibo_data) const
		{
			//data
			uint32_t vbo_index = m_vbo_index[0] + Group::vbo_size(0);
			uint32_t* ibo_ptr = ibo_data[1] + m_ibo_index[1] + Group::ibo_size(1);
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
			vertices::Model3D* vbo_ptr = (vertices::Model3D*) vbo_data[0] + m_vbo_index[0] + Group::vbo_size(0);
			//vbo data
			for(uint32_t i = 0; i <= m_mesh; i++)
			{
				const float s = i * path_max() / m_mesh;
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = path_position(s);
			}
		}

		void Path::setup(uint32_t vbo_counter[], uint32_t ibo_counter[])
		{
			for(Geometry* geometry : m_geometries)
			{
				if(dynamic_cast<Arrow*>(geometry))
				{
					float s = ((Arrow*) geometry)->m_parameter;
					((Arrow*) geometry)->m_point = path_position(s);
					((Arrow*) geometry)->m_directions[0] = path_normal(s);
					((Arrow*) geometry)->m_directions[1] = path_binormal(s);
				}
			}
			Group::setup(vbo_counter, ibo_counter);
		}
		void Path::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
			Group::buffers_data(vbo_data, ibo_data);
		}
	}
}