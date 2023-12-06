//std
#include <cstring>

//canvas
#include "inc/Objects/Group.hpp"
#include "inc/Vertices/Text.hpp"
#include "inc/Vertices/Model.hpp"
#include "inc/Vertices/Image.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Group::Group(void)
		{
			return;
		}

		//destructor
		Group::~Group(void)
		{
			for(const Geometry* geometry : m_geometries)
			{
				delete geometry;
			}
		}

		//data
		bool Group::dot(bool dot)
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->m_dot = dot;
			}
			return m_dot = dot;
		}
		bool Group::fill(bool fill)
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->m_fill = fill;
			}
			return m_fill = fill;
		}
		bool Group::stroke(bool stroke)
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->m_stroke = stroke;
			}
			return m_stroke = stroke;
		}

		Color Group::color_dot(const Color& color_dot)
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->m_color_dot = color_dot;
			}
			return m_color_dot = color_dot;
		}
		Color Group::color_fill(const Color& color_fill)
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->m_color_fill = color_fill;
			}
			return m_color_fill = color_fill;
		}
		Color Group::color_stroke(const Color& color_stroke)
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->m_color_stroke = color_stroke;
			}
			return m_color_stroke = color_stroke;
		}

		//buffers
		unsigned Group::vbo_size(unsigned index) const
		{
			unsigned s = 0;
			for(const Geometry* geometry : m_geometries)
			{
				s += geometry->vbo_size(index);
			}
			return s;
		}
		unsigned Group::ibo_size(unsigned index) const
		{
			unsigned s = 0;
			for(const Geometry* geometry : m_geometries)
			{
				s += geometry->ibo_size(index);
			}
			return s;
		}

		//draw
		void Group::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			//data
			unsigned vbo_group_counter[3], ibo_group_counter[6];
			memcpy(vbo_group_counter, vbo_counter, 3 * sizeof(unsigned));
			memcpy(ibo_group_counter, ibo_counter, 6 * sizeof(unsigned));
			//indexes
			for(Geometry* geometry : m_geometries)
			{
				geometry->setup(vbo_group_counter, ibo_group_counter);
			}
			Object::setup(vbo_counter, ibo_counter);
		}
		void Group::vbo_model_matrix(vertices::Vertex** vbo_data) const
		{
			for(unsigned i = 0; i < 3; i++)
			{
				unsigned vbo_index = m_vbo_index[i];
				for(const Geometry* geometry : m_geometries)
				{
					for(unsigned j = 0; j < geometry->vbo_size(i); j++)
					{
						if(i == 2) ((vertices::Text*) vbo_data[i] + vbo_index + j)->m_position *= geometry->model_matrix();
						if(i == 0) ((vertices::Model*) vbo_data[i] + vbo_index + j)->m_position *= geometry->model_matrix();
						if(i == 1) ((vertices::Image*) vbo_data[i] + vbo_index + j)->m_position *= geometry->model_matrix();
					}
					vbo_index += geometry->vbo_size(i);
				}
			}
		}
		void Group::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			for(const Geometry* geometry : m_geometries)
			{
				geometry->buffers_data(vbo_data, ibo_data);
			}
			vbo_model_matrix(vbo_data);
		}
	}
}