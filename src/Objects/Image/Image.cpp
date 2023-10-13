//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Scene/Image.hpp"
#include "inc/Vertices/Image.hpp"
#include "inc/Objects/Image/Image.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Image::Image(void) : m_size(1), m_position{0, 0, 0}, m_image(0), m_directions{{1, 0, 0}, {0, 1, 0}}
		{
			return;
		}

		//destructor
		Image::~Image(void)
		{
			return;
		}

		//data
		float Image::size(void) const
		{
			return m_size;
		}
		float Image::size(float size)
		{
			return m_size = size;
		}

		Anchor Image::anchor(void) const
		{
			return m_anchor;
		}
		Anchor Image::anchor(Anchor anchor)
		{
			return m_anchor = anchor;
		}

		vec3 Image::position(void) const
		{
			return m_position;
		}
		vec3 Image::position(const vec3& position)
		{
			return m_position = position;
		}

		unsigned Image::image(void) const
		{
			return m_image;
		}
		unsigned Image::image(unsigned image)
		{
			return m_image = image;
		}

		vec3 Image::direction(unsigned index) const
		{
			return m_directions[index];
		}
		vec3 Image::direction(unsigned index, const vec3& direction)
		{
			return m_directions[index] = direction;
		}

		//buffers
		unsigned Image::vbo_size(unsigned index) const
		{
			return 4 * (index == 1);
		}
		unsigned Image::ibo_size(unsigned index) const
		{
			return 2 * (index == 3);
		}

		//draw
		void Image::ibo_fill_data(unsigned** ibo_data) const
		{
			ibo_data[3][m_ibo_index[3] + 3 * 0 + 0] = m_vbo_index[1] + 0;
			ibo_data[3][m_ibo_index[3] + 3 * 0 + 1] = m_vbo_index[1] + 1;
			ibo_data[3][m_ibo_index[3] + 3 * 0 + 2] = m_vbo_index[1] + 2;
			ibo_data[3][m_ibo_index[3] + 3 * 1 + 0] = m_vbo_index[1] + 0;
			ibo_data[3][m_ibo_index[3] + 3 * 1 + 1] = m_vbo_index[1] + 2;
			ibo_data[3][m_ibo_index[3] + 3 * 1 + 2] = m_vbo_index[1] + 3;
		}
		void Image::vbo_fill_data(vertices::Vertex** vbo_data) const
		{
			//data
			const vec3& t1 = m_directions[0];
			const vec3& t2 = m_directions[1];
			const unsigned wi = m_scene->image(m_image).m_width;
			const unsigned hi = m_scene->image(m_image).m_height;
			const unsigned xi = m_scene->image(m_image).m_offset;
			//vertices
			const float w = m_size;
			const float h = m_size * hi / wi;
			const float x[][2] = {{0, 0}, {w, 0}, {w, h}, {0, h}};
			const float t[][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
			for(unsigned i = 0; i < 4; i++)
			{
				((vertices::Image*) vbo_data[1] + m_vbo_index[1] + i)->m_texture = t[i];
				((vertices::Image*) vbo_data[1] + m_vbo_index[1] + i)->m_position = m_position + x[i][0] * t1 + x[i][1] * t2;
			}
		}
		void Image::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			vbo_fill_data(vbo_data);
			ibo_fill_data(ibo_data);
		}
	}
}