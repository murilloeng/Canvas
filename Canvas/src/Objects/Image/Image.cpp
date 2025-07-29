//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Textures/Image.hpp"

#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

#include "Canvas/Canvas/inc/Objects/Image/Image.hpp"

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

		uint32_t Image::index(void) const
		{
			return m_index;
		}
		uint32_t Image::index(uint32_t index)
		{
			return m_index = index;
		}

		vec3 Image::direction(uint32_t index) const
		{
			return m_directions[index];
		}
		vec3 Image::direction(uint32_t index, const vec3& direction)
		{
			return m_directions[index] = direction;
		}

		//setup
		void Image::setup(void)
		{
			if(m_index >= m_scene->images().size())
			{
				throw std::runtime_error("Error: Image has out of range index!");
			}
			Object::setup();
		}

		//buffers
		void Image::buffers_size(void)
		{
			m_vbo_size[1] = 4 * m_fill;
			m_ibo_size[3] = 6 * m_fill;
		}
		void Image::buffers_data(void) const
		{
			//data
			float tc[4];
			if(!m_fill) return;
			uint32_t* ibo_ptr = ibo_data(3);
			const vec3& t1 = m_directions[0];
			const vec3& t2 = m_directions[1];
			m_scene->image(m_index)->coordinates(tc);
			vertices::Image3D* vbo_ptr = vbo_data_image_3D();
			const uint32_t wi = m_scene->image(m_index)->width();
			const uint32_t hi = m_scene->image(m_index)->height();
			//vbo data
			const float w = m_size;
			const float h = m_size * hi / wi;
			const float x[][2] = {{0, 0}, {w, 0}, {w, h}, {0, h}};
			const float t[][2] = {{tc[0], tc[2]}, {tc[1], tc[2]}, {tc[1], tc[3]}, {tc[0], tc[3]}};
			for(uint32_t i = 0; i < 4; i++)
			{
				const float x2 = x[i][1] - m_anchor.vertical() * h / 2;
				const float x1 = x[i][0] - m_anchor.horizontal() * w / 2;
				vbo_ptr[i].m_texture_coordinates = t[i];
				vbo_ptr[i].m_position = m_position + x1 * t1 + x2 * t2;
			}
			//ibo data
			ibo_ptr[3 * 0 + 0] = m_vbo_index[1] + 0;
			ibo_ptr[3 * 0 + 1] = m_vbo_index[1] + 1;
			ibo_ptr[3 * 0 + 2] = m_vbo_index[1] + 2;
			ibo_ptr[3 * 1 + 0] = m_vbo_index[1] + 0;
			ibo_ptr[3 * 1 + 1] = m_vbo_index[1] + 2;
			ibo_ptr[3 * 1 + 2] = m_vbo_index[1] + 3;
		}
	}
}