//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/Scene/Light.hpp"
#include "Canvas/inc/GPU/Program.hpp"

namespace canvas
{
	//constructor
	Light::Light(void) :
		m_alpha(32), m_ambient(false), m_diffuse(false), m_specular(false), m_position(0, 0, 0),
		m_color_ambient(0.2f, 0.2f, 0.2f), m_color_diffuse(1.0f, 1.0f, 1.0f), m_color_specular(1.0f, 1.0f, 1.0f)
	{
		return;
	}
	
	//destructor
	Light::~Light(void)
	{
		return;
	}
	
	//data
	bool Light::ambient(void) const
	{
		return m_ambient;
	}
	bool Light::ambient(bool ambient)
	{
		return m_ambient = ambient;
	}

	bool Light::diffuse(void) const
	{
		return m_diffuse;
	}
	bool Light::diffuse(bool diffuse)
	{
		return m_diffuse = diffuse;
	}

	bool Light::specular(void) const
	{
		return m_specular;
	}
	bool Light::specular(bool specular)
	{
		return m_specular = specular;
	}

	vec3 Light::position(void) const
	{
		return m_position;
	}
	vec3 Light::position(vec3 position)
	{
		return m_position = position;
	}

	Color Light::color_ambient(void) const
	{
		return m_color_ambient;
	}
	Color Light::color_ambient(Color color_ambient)
	{
		return m_color_ambient = color_ambient;
	}

	Color Light::color_diffuse(void) const
	{
		return m_color_diffuse;
	}
	Color Light::color_diffuse(Color color_diffuse)
	{
		return m_color_diffuse = color_diffuse;
	}

	Color Light::color_specular(void) const
	{
		return m_color_specular;
	}
	Color Light::color_specular(Color color_specular)
	{
		return m_color_specular = color_specular;
	}

	//shaders
	void Light::update_shaders(void) const
	{
		m_program->use();
		glUniform1f(m_program->uniform("light_alpha"), m_alpha);
		glUniform1i(m_program->uniform("light_ambient"), m_ambient);
		glUniform1i(m_program->uniform("light_diffuse"), m_diffuse);
		glUniform1i(m_program->uniform("light_specular"), m_specular);
		glUniform3fv(m_program->uniform("light_position"), 1, m_position.data());
		glUniform4fv(m_program->uniform("light_color_ambient"), 1, m_color_ambient.channels());
		glUniform4fv(m_program->uniform("light_color_diffuse"), 1, m_color_diffuse.channels());
		glUniform4fv(m_program->uniform("light_color_specular"), 1, m_color_specular.channels());
	}

	//callbacks
	void Light::callback_keyboard(char key, int, int)
	{
		if(key == 'a') ambient(!m_ambient);
		if(key == 'd') diffuse(!m_diffuse);
		if(key == 's') specular(!m_specular);
		update_shaders();
	}
}