//canvas
#include "inc/Scene/Font.hpp"
#include "inc/Scene/Scene.hpp"
#include "inc/Vertices/Text.hpp"
#include "inc/Objects/Image/Text.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Text::Text(void) : m_font(0), m_size(16), m_position{0, 0, 0}, m_directions{{1, 0, 0}, {0, 1, 0}}
		{
			return;
		}

		//destructor
		Text::~Text(void)
		{
			return;
		}

		//data
		unsigned Text::font(void) const
		{
			return m_font;
		}
		unsigned Text::font(unsigned font)
		{
			return m_font = font;
		}

		unsigned Text::size(void) const
		{
			return m_size;
		}
		unsigned Text::size(unsigned size)
		{
			return m_size = size;
		}

		Anchor Text::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Text::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		vec3 Text::position(void) const
		{
			return m_position;
		}
		vec3 Text::position(const vec3& position)
		{
			return m_position = position;
		}

		std::string Text::text(void) const
		{
			return m_text;
		}
		std::string Text::text(std::string text)
		{
			return m_text = text;
		}

		vec3 Text::direction(unsigned index) const
		{
			return m_directions[index];
		}
		vec3 Text::direction(unsigned index, const vec3& direction)
		{
			return m_directions[index] = direction;
		}

		//buffers
		unsigned Text::vbo_size(unsigned index) const
		{
			return 4 * (index == 2);
		}
		unsigned Text::ibo_size(unsigned index) const
		{
			return 2 * (index == 4);
		}

		//draw
		void Text::ibo_fill_data(unsigned** ibo_data) const
		{
			ibo_data[4][m_ibo_index[4] + 3 * 0 + 0] = m_vbo_index[2] + 0;
			ibo_data[4][m_ibo_index[4] + 3 * 0 + 1] = m_vbo_index[2] + 1;
			ibo_data[4][m_ibo_index[4] + 3 * 0 + 2] = m_vbo_index[2] + 2;
			ibo_data[4][m_ibo_index[4] + 3 * 1 + 0] = m_vbo_index[2] + 0;
			ibo_data[4][m_ibo_index[4] + 3 * 1 + 1] = m_vbo_index[2] + 2;
			ibo_data[4][m_ibo_index[4] + 3 * 1 + 2] = m_vbo_index[2] + 3;
		}
		void Text::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			float tc[4];
			const vec3& t1 = m_directions[0];
			const vec3& t2 = m_directions[1];
			const unsigned ws = m_scene->camera().width();
			const unsigned hs = m_scene->camera().height();
			//vertices
			const float w = 1;
			const float h = 1;
			const float x[][2] = {{0, 0}, {w, 0}, {w, h}, {0, h}};
			const float t[][2] = {{tc[0], tc[2]}, {tc[1], tc[2]}, {tc[1], tc[3]}, {tc[0], tc[3]}};
			for(unsigned i = 0; i < m_text.length(); i++)
			{
				m_scene->font(m_font)->character(m_text[i]).coordinates(tc);

			}
			for(unsigned i = 0; i < 4; i++)
			{
				((vertices::Text*) vbo_data[2] + m_vbo_index[2] + i)->m_color_text = m_color_fill;
				((vertices::Text*) vbo_data[2] + m_vbo_index[2] + i)->m_texture_coordinates = t[i];
				((vertices::Text*) vbo_data[2] + m_vbo_index[2] + i)->m_position = m_position + x[i][0] * t1 + x[i][1] * t2;
			}
		}

		void Text::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			if(m_font >= m_scene->fonts().size())
			{
				fprintf(stderr, "Error: Text's font has out of range index!\n");
				exit(EXIT_FAILURE);
			}
			Object::setup(vbo_counter, ibo_counter);
		}
		void Text::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			vbo_fill_data(vbo_data);
			ibo_fill_data(ibo_data);
		}
	}
}