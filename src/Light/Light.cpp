//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/Light/Light.hpp"
#include "Canvas/inc/GPU/Program.hpp"

namespace canvas
{
	namespace lights
	{
		//constructor
		Light::Light(void) : m_ambient(nullptr)
		{
			return;
		}

		//destructor
		Light::~Light(void)
		{
			return;
		}
		
		//data
		Ambient* Light::ambient(void) const
		{
			return m_ambient;
		}
		Point* Light::point(uint32_t index) const
		{
			return m_points[index];
		}
		Direction* Light::direction(uint32_t index) const
		{
			return m_diredtions[index];
		}

		const std::vector<Point*> Light::points(void) const
		{
			return m_points;
		}
		const std::vector<Direction*> Light::directions(void) const
		{
			return m_diredtions;
		}

		//shaders
		void Light::update_shaders(void) const
		{
			m_program->bind();
			// m_program->set_uniform("light_alpha", m_alpha);
			// m_program->set_uniform("light_ambient", m_ambient);
			// m_program->set_uniform("light_diffuse", m_diffuse);
			// m_program->set_uniform("light_specular", m_specular);
			// m_program->set_uniform("light_position", m_position.data(), 3);
			// m_program->set_uniform("light_color_ambient", m_color_ambient.channels(), 4);
			// m_program->set_uniform("light_color_diffuse", m_color_diffuse.channels(), 4);
			// m_program->set_uniform("light_color_specular", m_color_specular.channels(), 4);
		}
	}
}