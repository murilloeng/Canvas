//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"
#include "inc/Objects/Curves/Arrow.hpp"
#include "inc/Objects/Curves/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Curve::Curve(void) : m_mesh(40)
		{
			return;
		}

		//destructor
		Curve::~Curve(void)
		{
			return;
		}

		//data
		unsigned Curve::mesh(void) const
		{
			return m_mesh;
		}
		unsigned Curve::mesh(unsigned mesh)
		{
			return m_mesh = mesh;
		}

		//arrows
		void Curve::add_arrow(float s, bool sense)
		{
			//data
			Arrow* arrow = new Arrow;
			//arrow
			arrow->parameter(s);
			arrow->sense(sense);
			m_objects.push_back(arrow);
		}
		void Curve::remove_arrow(unsigned index)
		{
			unsigned counter = 0;
			for(unsigned i = 0; i < m_objects.size(); i++)
			{
				if(dynamic_cast<const Arrow*>(m_objects[i]))
				{
					if(counter == index)
					{
						delete m_objects[i];
						m_objects.erase(m_objects.begin() + i);
					}
					counter++;
				}
			}
		}
		unsigned Curve::arrows(void) const
		{
			unsigned counter = 0;
			for(const Object* object : m_objects)
			{
				if(dynamic_cast<const Arrow*>(object))
				{
					counter++;
				}
			}
			return counter;
		}
		Arrow* Curve::arrow(unsigned index) const
		{
			unsigned counter = 0;
			for(Object* object : m_objects)
			{
				if(dynamic_cast<Arrow*>(object))
				{
					if(counter != index)
					{
						counter++;
					}
					else
					{
						return (Arrow*) object;
					}
				}
			}
			return nullptr;
		}

		//path
		float Curve::path_max(void) const
		{
			return 1.0f;
		}
		vec3 Curve::path_normal(float s) const
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
		vec3 Curve::path_tangent(float s) const
		{
			return path_gradient(s).unit();
		}
		vec3 Curve::path_binormal(float s) const
		{
			return path_tangent(s).cross(path_normal(s));
		}

		//sizes
		unsigned Curve::vbo_size(void) const
		{
			return Group::vbo_size() + (m_mesh + 1) * m_stroke;
		}
		unsigned Curve::ibo_size(unsigned index) const
		{
			return Group::ibo_size(index) + m_mesh * (index == 1) * m_stroke;
		}

		//buffers
		void Curve::ibo_stroke_data(unsigned** ibo_data) const
		{
			//data
			unsigned vbo_index = m_vbo_index[0] + Group::vbo_size();
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1] + 2 * Group::ibo_size(1);
			//ibo data
			for(unsigned i = 0; i < m_mesh; i++)
			{
				ibo_ptr[2 * i + 0] = vbo_index + i + 0;
				ibo_ptr[2 * i + 1] = vbo_index + i + 1;
			}
		}
		void Curve::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index[0] + Group::vbo_size();
			//vbo data
			for(unsigned i = 0; i <= m_mesh; i++)
			{
				const float s = i * path_max() / m_mesh;
				(vbo_ptr + i)->m_color = m_color_stroke;
				(vbo_ptr + i)->m_position = path_position(s);
			}
		}
		void Curve::buffers_index(unsigned& vbo_counter, unsigned ibo_counter[])
		{
			for(Object* object : m_objects)
			{
				if(dynamic_cast<Arrow*>(object))
				{
					float s = ((Arrow*) object)->m_parameter;
					((Arrow*) object)->m_point = path_position(s);
					((Arrow*) object)->m_directions[0] = path_normal(s);
					((Arrow*) object)->m_directions[1] = path_binormal(s);
				}
			}
			Group::buffers_index(vbo_counter, ibo_counter);
		}
		void Curve::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			if(m_stroke) vbo_stroke_data(vbo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
			Group::buffers_data(vbo_data, ibo_data);
		}
	}
}