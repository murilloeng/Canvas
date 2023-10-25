//ext
#include "ext/inc/GL/glew.h"

//canvas
#include "inc/Scene/Light.hpp"
#include "inc/GPU/Program.hpp"

namespace canvas
{
	//constructor
	Light::Light(void) : m_ambient(false), m_diffuse(false), m_specular(false), m_position(0, 0, 1)
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
		m_program->use();
		glUniform1i(glGetUniformLocation(m_program->id(), "light_ambient"), ambient);
		return m_ambient = ambient;
	}

	bool Light::diffuse(void) const
	{
		return m_diffuse;
	}
	bool Light::diffuse(bool diffuse)
	{
		m_program->use();
		glUniform1i(glGetUniformLocation(m_program->id(), "light_diffuse"), diffuse);
		return m_diffuse = diffuse;
	}

	bool Light::specular(void) const
	{
		return m_specular;
	}
	bool Light::specular(bool specular)
	{
		m_program->use();
		glUniform1i(glGetUniformLocation(m_program->id(), "light_specular"), specular);
		return m_specular = specular;
	}

	vec3 Light::position(void) const
	{
		return m_position;
	}
	vec3 Light::position(vec3 position)
	{
		m_program->use();
		glUniform3f(glGetUniformLocation(m_program->id(), "light_position"), position[0], position[1], position[2]);
		return m_position = position;
	}

	Color Light::color_ambient(void) const
	{
		return m_color_ambient;
	}
	Color Light::color_ambient(Color color_ambient)
	{
		m_program->use();
		unsigned location = glGetUniformLocation(m_program->id(), "light_color_ambient");
		glUniform4f(location, color_ambient[0], color_ambient[1], color_ambient[2], color_ambient[3]);
		return m_color_ambient = color_ambient;
	}

	Color Light::color_diffuse(void) const
	{
		return m_color_diffuse;
	}
	Color Light::color_diffuse(Color color_diffuse)
	{
		m_program->use();
		unsigned location = glGetUniformLocation(m_program->id(), "light_color_diffuse");
		glUniform4f(location, color_diffuse[0], color_diffuse[1], color_diffuse[2], color_diffuse[3]);
		return m_color_diffuse = color_diffuse;
	}

	Color Light::color_specular(void) const
	{
		return m_color_specular;
	}
	Color Light::color_specular(Color color_specular)
	{
		m_program->use();
		unsigned location = glGetUniformLocation(m_program->id(), "light_color_specular");
		glUniform4f(location, color_specular[0], color_specular[1], color_specular[2], color_specular[3]);
		return m_color_specular = color_specular;
	}

	//callbacks
	void Light::callback_keyboard(char key, int, int)
	{
		if(key == 'a') ambient(!m_ambient);
		if(key == 'd') diffuse(!m_diffuse);
		if(key == 's') specular(!m_specular);
	}
}