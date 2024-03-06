//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Scene/Latex.hpp"
#include "Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/inc/Objects/Image/Latex.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Latex::Latex(void) : m_size(1), m_position{0, 0, 0}, m_index(0), m_directions{{1, 0, 0}, {0, 1, 0}}
		{
			return;
		}

		//destructor
		Latex::~Latex(void)
		{
			return;
		}

		//data
		float Latex::size(void) const
		{
			return m_size;
		}
		float Latex::size(float size)
		{
			return m_size = size;
		}

		Anchor Latex::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Latex::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		vec3 Latex::position(void) const
		{
			return m_position;
		}
		vec3 Latex::position(const vec3& position)
		{
			return m_position = position;
		}

		unsigned Latex::index(void) const
		{
			return m_index;
		}
		unsigned Latex::index(unsigned index)
		{
			return m_index = index;
		}

		vec3 Latex::direction(unsigned index) const
		{
			return m_directions[index];
		}
		vec3 Latex::direction(unsigned index, const vec3& direction)
		{
			return m_directions[index] = direction;
		}

		//buffers
		unsigned Latex::vbo_size(unsigned index) const
		{
			return 4 * m_fill * (index == 2);
		}
		unsigned Latex::ibo_size(unsigned index) const
		{
			return 2 * m_fill * (index == 5);
		}

		//draw
		void Latex::ibo_fill_data(unsigned** ibo_data) const
		{
			ibo_data[5][m_ibo_index[5] + 3 * 0 + 0] = m_vbo_index[2] + 0;
			ibo_data[5][m_ibo_index[5] + 3 * 0 + 1] = m_vbo_index[2] + 1;
			ibo_data[5][m_ibo_index[5] + 3 * 0 + 2] = m_vbo_index[2] + 2;
			ibo_data[5][m_ibo_index[5] + 3 * 1 + 0] = m_vbo_index[2] + 0;
			ibo_data[5][m_ibo_index[5] + 3 * 1 + 1] = m_vbo_index[2] + 2;
			ibo_data[5][m_ibo_index[5] + 3 * 1 + 2] = m_vbo_index[2] + 3;
		}
		void Latex::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			float tc[4];
			const vec3& t1 = m_directions[0];
			const vec3& t2 = m_directions[1];
			m_scene->latex(m_index)->coordinates(tc);
			const unsigned wi = m_scene->latex(m_index)->width();
			const unsigned hi = m_scene->latex(m_index)->height();
			//vertices
			const float h = m_size;
			const float w = m_size * wi / hi;
			const float x[][2] = {{0, 0}, {w, 0}, {w, h}, {0, h}};
			const float t[][2] = {{tc[0], tc[2]}, {tc[1], tc[2]}, {tc[1], tc[3]}, {tc[0], tc[3]}};
			for(unsigned i = 0; i < 4; i++)
			{
				const float x2 = x[i][1] - m_anchor.vertical() * h / 2;
				const float x1 = x[i][0] - m_anchor.horizontal() * w / 2;
				((vertices::Text3D*) vbo_data[2] + m_vbo_index[2] + i)->m_color = m_color_fill;
				((vertices::Text3D*) vbo_data[2] + m_vbo_index[2] + i)->m_texture_coordinates = t[i];
				((vertices::Text3D*) vbo_data[2] + m_vbo_index[2] + i)->m_position = m_position + x1 * t1 + x2 * t2;
			}
		}

		void Latex::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			if(m_index >= m_scene->latex().size())
			{
				fprintf(stderr, "Error: Equation has out of range index!\n");
				exit(EXIT_FAILURE);
			}
			Object::setup(vbo_counter, ibo_counter);
		}
		void Latex::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}
	}
}