//std
#include <cstring>

//canvas
#include "Canvas/inc/Objects/Group.hpp"
#include "Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Vertices/Image3D.hpp"

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
		void Group::vbo_size(uint32_t vbo_counter[]) const
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->vbo_size(vbo_counter);
			}
		}
		void Group::ibo_size(uint32_t ibo_counter[]) const
		{
			for(Geometry* geometry : m_geometries)
			{
				geometry->ibo_size(ibo_counter);
			}
		}

		//draw
		void Group::setup(uint32_t vbo_counter[], uint32_t ibo_counter[])
		{
			//data
			uint32_t vbo_group_counter[3], ibo_group_counter[6];
			memcpy(vbo_group_counter, vbo_counter, 3 * sizeof(uint32_t));
			memcpy(ibo_group_counter, ibo_counter, 6 * sizeof(uint32_t));
			//indexes
			for(Geometry* geometry : m_geometries)
			{
				geometry->setup(vbo_group_counter, ibo_group_counter);
			}
			Object::setup(vbo_counter, ibo_counter);
		}
		void Group::vbo_model_matrix(vertices::Vertex** vbo_data) const
		{
			uint32_t vbo_offset[12];
			memset(vbo_offset, 0, sizeof(vbo_offset));
			for(const Geometry* geometry : m_geometries)
			{
				geometry->vbo_size(vbo_offset);
				for(uint32_t i = 0; i < 3; i++)
				{
					for(uint32_t j = vbo_offset[i + 6]; j < vbo_offset[i]; j++)
					{
						if(i == 2) ((vertices::Text3D*) vbo_data[i] + m_vbo_index[i] + j)->m_position *= geometry->model_matrix();
						if(i == 0) ((vertices::Model3D*) vbo_data[i] + m_vbo_index[i] + j)->m_position *= geometry->model_matrix();
						if(i == 1) ((vertices::Image3D*) vbo_data[i] + m_vbo_index[i] + j)->m_position *= geometry->model_matrix();
					}
				}
				memcpy(vbo_offset + 6, vbo_offset, 6 * sizeof(uint32_t));
			}
		}
		void Group::buffers_data(vertices::Vertex** vbo_data, uint32_t** ibo_data) const
		{
			for(const Geometry* geometry : m_geometries)
			{
				geometry->buffers_data(vbo_data, ibo_data);
			}
			vbo_model_matrix(vbo_data);
		}
	}
}