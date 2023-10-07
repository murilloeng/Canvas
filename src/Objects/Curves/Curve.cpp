//std
#include <cmath>

//canvas
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
		void Curve::add_arrow(float s, bool inversed)
		{
			//data
			Arrow* arrow = new Arrow;
			const vec3 t2 = path_normal(s);
			const vec3 t1 = path_tangent(s);
			const vec3 t3 = path_binormal(s);
			const vec3 xp = path_position(s);
			//arrow
			arrow->point(xp);
			arrow->parameter(s);
			arrow->direction(0, t2);
			arrow->direction(1, t3);
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

		//buffers
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
	}
}