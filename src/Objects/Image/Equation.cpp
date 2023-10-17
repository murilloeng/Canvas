//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Vertices/Text.hpp"
#include "inc/Scene/Equation.hpp"
#include "inc/Objects/Image/Equation.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Equation::Equation(void) : m_size(1), m_position{0, 0, 0}, m_index(0), m_directions{{1, 0, 0}, {0, 1, 0}}
		{
			return;
		}

		//destructor
		Equation::~Equation(void)
		{
			return;
		}

		//data
		float Equation::size(void) const
		{
			return m_size;
		}
		float Equation::size(float size)
		{
			return m_size = size;
		}

		Anchor Equation::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Equation::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		vec3 Equation::position(void) const
		{
			return m_position;
		}
		vec3 Equation::position(const vec3& position)
		{
			return m_position = position;
		}

		unsigned Equation::index(void) const
		{
			return m_index;
		}
		unsigned Equation::index(unsigned index)
		{
			return m_index = index;
		}

		vec3 Equation::direction(unsigned index) const
		{
			return m_directions[index];
		}
		vec3 Equation::direction(unsigned index, const vec3& direction)
		{
			return m_directions[index] = direction;
		}

		//buffers
		unsigned Equation::vbo_size(unsigned index) const
		{
			return 4 * m_fill * (index == 2);
		}
		unsigned Equation::ibo_size(unsigned index) const
		{
			return 2 * m_fill * (index == 5);
		}

		//draw
		void Equation::ibo_fill_data(unsigned** ibo_data) const
		{
			ibo_data[5][m_ibo_index[5] + 3 * 0 + 0] = m_vbo_index[2] + 0;
			ibo_data[5][m_ibo_index[5] + 3 * 0 + 1] = m_vbo_index[2] + 1;
			ibo_data[5][m_ibo_index[5] + 3 * 0 + 2] = m_vbo_index[2] + 2;
			ibo_data[5][m_ibo_index[5] + 3 * 1 + 0] = m_vbo_index[2] + 0;
			ibo_data[5][m_ibo_index[5] + 3 * 1 + 1] = m_vbo_index[2] + 2;
			ibo_data[5][m_ibo_index[5] + 3 * 1 + 2] = m_vbo_index[2] + 3;
		}
		void Equation::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			float tc[4];
			const vec3& t1 = m_directions[0];
			const vec3& t2 = m_directions[1];
			m_scene->equation(m_index)->coordinates(tc);
			const unsigned wi = m_scene->equation(m_index)->width();
			const unsigned hi = m_scene->equation(m_index)->height();
			//vertices
			const float w = m_size;
			const float h = m_size * hi / wi;
			const float x[][2] = {{0, 0}, {w, 0}, {w, h}, {0, h}};
			const float t[][2] = {{tc[0], tc[2]}, {tc[1], tc[2]}, {tc[1], tc[3]}, {tc[0], tc[3]}};
			for(unsigned i = 0; i < 4; i++)
			{
				const float x2 = x[i][1] - m_anchor.vertical() * h / 2;
				const float x1 = x[i][0] - m_anchor.horizontal() * w / 2;
				((vertices::Text*) vbo_data[2] + m_vbo_index[2] + i)->m_color = m_color_fill;
				((vertices::Text*) vbo_data[2] + m_vbo_index[2] + i)->m_texture_coordinates = t[i];
				((vertices::Text*) vbo_data[2] + m_vbo_index[2] + i)->m_position = m_position + x1 * t1 + x2 * t2;
			}
		}

		void Equation::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			if(m_index >= m_scene->equations().size())
			{
				fprintf(stderr, "Error: Equation has out of range index!\n");
				exit(EXIT_FAILURE);
			}
			Object::setup(vbo_counter, ibo_counter);
		}
		void Equation::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}
	}
}