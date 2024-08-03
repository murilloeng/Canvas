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

		//setup
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

		//model
		void Group::vbo_model_matrix(vertices::Vertex** vbo_data) const
		{
			for(uint32_t i = 0; i < 3; i++)
			{
				uint32_t vbo_index = m_vbo_index[i];
				for(const Geometry* geometry : m_geometries)
				{
					for(uint32_t j = 0; j < geometry->m_vbo_size[i]; j++)
					{
						if(i == 2) ((vertices::Text3D*) vbo_data[i] + vbo_index + j)->m_position *= geometry->model_matrix();
						if(i == 0) ((vertices::Model3D*) vbo_data[i] + vbo_index + j)->m_position *= geometry->model_matrix();
						if(i == 1) ((vertices::Image3D*) vbo_data[i] + vbo_index + j)->m_position *= geometry->model_matrix();
					}
					vbo_index += geometry->m_vbo_size[i];
				}
			}
		}

		//buffers
		void Group::buffers_size(void)
		{
			memset(m_vbo_size, 0, sizeof(m_vbo_size));
			memset(m_ibo_size, 0, sizeof(m_ibo_size));
			for(Geometry* geometry : m_geometries)
			{
				geometry->buffers_size();
				for(uint32_t i = 0; i <  6; i++) m_vbo_size[i] += geometry->m_vbo_size[i];
				for(uint32_t i = 0; i < 12; i++) m_ibo_size[i] += geometry->m_ibo_size[i];
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