//std
#include <cmath>
#include <cstdio>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Grid_3D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Grid_3D::Grid_3D(void) : m_grids(new Grid_2D[3]), m_mesh{10, 10, 10}
		{
			m_fill_colors.resize(1);
			m_stroke_colors.resize(1);
		}

		//destructor
		Grid_3D::~Grid_3D(void)
		{
			delete[] m_grids;
		}

		//data
		bool Grid_3D::fill(bool fill)
		{
			for(unsigned i = 0; i < 3; i++)
			{
				m_grids[i].fill(fill);
			}
			return m_fill = fill;
		}
		bool Grid_3D::stroke(bool stroke)
		{
			for(unsigned i = 0; i < 3; i++)
			{
				m_grids[i].stroke(stroke);
			}
			return m_stroke = stroke;
		}

		void Grid_3D::fill_color(const Color& fill_color)
		{
			for(unsigned i = 0; i < 3; i++)
			{
				m_grids[i].fill_color(fill_color);
			}
			m_fill_colors[0] = fill_color;
		}
		void Grid_3D::fill_color(const Color& fill_color, unsigned)
		{

		}

		void Grid_3D::stroke_color(const Color& stroke_color)
		{
			for(unsigned i = 0; i < 3; i++)
			{
				m_grids[i].stroke_color(stroke_color);
			}
			m_stroke_colors[0] = stroke_color;
		}
		void Grid_3D::stroke_color(const Color& stroke_color, unsigned)
		{

		}

		unsigned Grid_3D::mesh(unsigned index) const
		{
			return m_mesh[index];
		}
		unsigned Grid_3D::mesh(unsigned index, unsigned mesh)
		{
			m_grids[(index + 0) % 3].mesh(0, mesh);
			m_grids[(index + 2) % 3].mesh(1, mesh);
			return m_mesh[index] = mesh;
		}

		//type
		objects::type Grid_3D::type(void) const
		{
			return objects::type::grid_3D;
		}

		//buffers
		unsigned Grid_3D::vbo_size(void) const
		{
			unsigned s = 0;
			for(unsigned i = 0; i < 3; i++)
			{
				s += m_grids[i].vbo_size();
			}
			return s;
		}
		unsigned Grid_3D::ibo_size(unsigned index) const
		{
			unsigned s = 0;
			for(unsigned i = 0; i < 3; i++)
			{
				s += m_grids[i].ibo_size(index);
			}
			return s;
		}

		//draw
		void Grid_3D::vbo_affine(vertices::Vertex* vbo_data) const
		{
			//data
			mat4 A[3];
			unsigned vbo_index = m_vbo_index;
			A[2] = mat4::shifting({0, 0, -1});
			A[0] = mat4::shifting({-1, 0, 0}) * mat4::rotation({0, M_PI_2, 0});
			A[1] = mat4::shifting({0, -1, 0}) * mat4::rotation({0, 0, M_PI_2}) * mat4::rotation({0, -M_PI_2, 0});
			//affine
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < m_grids[i].vbo_size(); j++)
				{
					((vertices::Model*) vbo_data + vbo_index + j)->m_position *= A[i];
				}
				vbo_index += m_grids[i].vbo_size();
			}
		}
		void Grid_3D::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//data
			unsigned ibo_index[] = {0, 0};
			unsigned vbo_index = m_vbo_index;
			//vbo index
			for(unsigned i = 0; i < 3; i++)
			{
				m_grids[i].m_vbo_index = vbo_index;
				vbo_index += m_grids[i].vbo_size();
			}
			//ibo index
			for(unsigned i = 0; i < 3; i++)
			{
				m_grids[i].m_ibo_index[1] = m_ibo_index[1] + ibo_index[0];
				m_grids[i].m_ibo_index[2] = m_ibo_index[2] + ibo_index[1];
				ibo_index[0] += 2 * m_grids[i].ibo_size(1);
				ibo_index[1] += 3 * m_grids[i].ibo_size(2);
			}
			//buffers data
			for(unsigned i = 0; i < 3; i++)
			{
				m_grids[i].buffers_data(vbo_data, ibo_data);
			}
			vbo_affine(vbo_data);
		}
	}
}