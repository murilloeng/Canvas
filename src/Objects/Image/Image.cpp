//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Scene/Image.hpp"
#include "Canvas/inc/Vertices/Image3D.hpp"
#include "Canvas/inc/Objects/Image/Image.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Image::Image(void) : m_size(1), m_position{0, 0, 0}, m_index(0), m_directions{{1, 0, 0}, {0, 1, 0}}
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

		unsigned Image::index(void) const
		{
			return m_index;
		}
		unsigned Image::index(unsigned index)
		{
			return m_index = index;
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
			return 4 * m_fill * (index == 1);
		}
		unsigned Image::ibo_size(unsigned index) const
		{
			return 2 * m_fill * (index == 3);
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
			float tc[4];
			const vec3& t1 = m_directions[0];
			const vec3& t2 = m_directions[1];
			m_scene->image(m_index)->coordinates(tc);
			const unsigned wi = m_scene->image(m_index)->width();
			const unsigned hi = m_scene->image(m_index)->height();
			//vertices
			const float w = m_size;
			const float h = m_size * hi / wi;
			const float x[][2] = {{0, 0}, {w, 0}, {w, h}, {0, h}};
			const float t[][2] = {{tc[0], tc[2]}, {tc[1], tc[2]}, {tc[1], tc[3]}, {tc[0], tc[3]}};
			for(unsigned i = 0; i < 4; i++)
			{
				const float x2 = x[i][1] - m_anchor.vertical() * h / 2;
				const float x1 = x[i][0] - m_anchor.horizontal() * w / 2;
				((vertices::Image3D*) vbo_data[1] + m_vbo_index[1] + i)->m_texture_coordinates = t[i];
				((vertices::Image3D*) vbo_data[1] + m_vbo_index[1] + i)->m_position = m_position + x1 * t1 + x2 * t2;
			}
		}

		void Image::setup(unsigned vbo_counter[], unsigned ibo_counter[])
		{
			if(m_index >= m_scene->images().size())
			{
				fprintf(stderr, "Error: Image has out of range index!\n");
				exit(EXIT_FAILURE);
			}
			Object::setup(vbo_counter, ibo_counter);
		}
		void Image::buffers_data(vertices::Vertex** vbo_data, unsigned** ibo_data) const
		{
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}
	}
}