//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"
#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

namespace canvas
{
	//constructors
	Shader::Shader(std::vector<Stage*> stages)
	{
		//create
		m_id = glCreateProgram();
		if(!glIsProgram(m_id))
		{
			throw std::runtime_error("Error creating shader program!");
		}
		//shaders
		for(Stage* stage : stages) glAttachShader(m_id, stage->m_id);
		//link
		GLint status;
		GLchar log[4096];
		glLinkProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &status);
		if(status == 0)
		{
			glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
			throw std::runtime_error("Error linking shader program: " + std::string(log));
		}
		//validate
		glValidateProgram(m_id);
		glGetProgramiv(m_id, GL_VALIDATE_STATUS, &status);
		if(status == 0)
		{
			glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
			throw std::runtime_error("Error validating shader program: " + std::string(log));
		}
		//delete
		for(Stage* stage : stages) delete stage;
	}

	//destructor
	Shader::~Shader(void)
	{
		if(glIsProgram(m_id)) glDeleteProgram(m_id);
	}

	//data
	GLuint Shader::id(void) const
	{
		return m_id;
	}

	//bind
	void Shader::bind(void) const
	{
		glUseProgram(m_id);
	}

	//uniforms
	GLint Shader::uniform_location(const char* name) const
	{
		//uniform
		GLint location = glGetUniformLocation(m_id, name);
		//check
		if(glGetError() != GL_NO_ERROR)
		{
			throw std::runtime_error("Error getting uniform " + std::string(name) + " location");
		}
		//return
		return location;
	}

	void Shader::set_uniform(const char* name, float v0) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform1f(location, v0);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, float v0, float v1) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform2f(location, v0, v1);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, float v0, float v1, float v2) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform3f(location, v0, v1, v2);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, float v0, float v1, float v2, float v3) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform4f(location, v0, v1, v2, v3);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}

	void Shader::set_uniform(const char* name, int32_t v0) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform1i(location, v0);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, int32_t v0, int32_t v1) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform2i(location, v0, v1);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, int32_t v0, int32_t v1, int32_t v2) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform3i(location, v0, v1, v2);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, int32_t v0, int32_t v1, int32_t v2, int32_t v3) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform4i(location, v0, v1, v2, v3);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}

	void Shader::set_uniform(const char* name, uint32_t v0) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform1ui(location, v0);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, uint32_t v0, uint32_t v1) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform2ui(location, v0, v1);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, uint32_t v0, uint32_t v1, uint32_t v2) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform3ui(location, v0, v1, v2);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform4ui(location, v0, v1, v2, v3);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}

	void Shader::set_uniform(const char* name, vec3 value) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniform3fv(location, 1, value.data());
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, mat4 value) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		glUniformMatrix4fv(location, 1, GL_FALSE, value.data());
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, const float* data, uint32_t size) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		if(size == 1) glUniform1fv(location, 1, data);
		if(size == 2) glUniform2fv(location, 1, data);
		if(size == 3) glUniform3fv(location, 1, data);
		if(size == 4) glUniform4fv(location, 1, data);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, const int32_t* data, uint32_t size) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		if(size == 1) glUniform1iv(location, 1, data);
		if(size == 2) glUniform2iv(location, 1, data);
		if(size == 3) glUniform3iv(location, 1, data);
		if(size == 4) glUniform4iv(location, 1, data);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform(const char* name, const uint32_t* data, uint32_t size) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		if(size == 1) glUniform1uiv(location, 1, data);
		if(size == 2) glUniform2uiv(location, 1, data);
		if(size == 3) glUniform3uiv(location, 1, data);
		if(size == 4) glUniform4uiv(location, 1, data);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}
	void Shader::set_uniform_matrix(const char* name, const float* data, uint32_t size) const
	{
		//data
		int32_t location = uniform_location(name);
		//check
		#ifdef _DEBUG
		check_uniform_location(name, location);
		#endif
		//uniform
		if(size == 2) glUniformMatrix2fv(location, 1, GL_FALSE, data);
		if(size == 3) glUniformMatrix3fv(location, 1, GL_FALSE, data);
		if(size == 4) glUniformMatrix4fv(location, 1, GL_FALSE, data);
		//check
		#ifdef _DEBUG
		check_uniform(name);
		#endif
	}

	//check
	void Shader::check_uniform(const char* name) const
	{
		if(glGetError() != GL_NO_ERROR)
		{
			throw std::runtime_error("Error getting uniform " + std::string(name) + "!");
		}
	}
	void Shader::check_uniform_location(const char* name, int32_t location) const
	{
		if(location == -1)
		{
			throw std::runtime_error("Error getting uniform " + std::string(name) + "location!");
		}
	}
}