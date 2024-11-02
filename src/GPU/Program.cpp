//canvas
#include "Canvas/inc/GPU/Shader.hpp"
#include "Canvas/inc/GPU/Program.hpp"

namespace canvas
{
	//constructors
	Program::Program(void) : m_id(0),
		m_vertex_shader(new Shader(GL_VERTEX_SHADER)),
		m_compute_shader(new Shader(GL_COMPUTE_SHADER)),
		m_geometry_shader(new Shader(GL_GEOMETRY_SHADER)),
		m_fragment_shader(new Shader(GL_FRAGMENT_SHADER)),
		m_tess_control_shader(new Shader(GL_TESS_CONTROL_SHADER)),
		m_tess_evaluation_shader(new Shader(GL_TESS_EVALUATION_SHADER))
	{
		return;
	}

	//destructor
	Program::~Program(void)
	{
		delete m_vertex_shader;
		delete m_compute_shader;
		delete m_geometry_shader;
		delete m_fragment_shader;
		delete m_tess_control_shader;
		delete m_tess_evaluation_shader;
		if(glIsProgram(m_id)) glDeleteProgram(m_id);
	}

	//data
	GLuint Program::id(void) const
	{
		return m_id;
	}
	Shader* Program::vertex_shader(void) const
	{
		return m_vertex_shader;
	}
	Shader* Program::compute_shader(void) const
	{
		return m_compute_shader;
	}
	Shader* Program::geometry_shader(void) const
	{
		return m_geometry_shader;
	}
	Shader* Program::fragment_shader(void) const
	{
		return m_fragment_shader;
	}
	Shader* Program::tess_control_shader(void) const
	{
		return m_tess_control_shader;
	}
	Shader* Program::tess_evaluation_shader(void) const
	{
		return m_tess_evaluation_shader;
	}

	//setup
	void Program::setup(void)
	{
		//create
		if((m_id = glCreateProgram()) == 0)
		{
			fprintf(stderr, "Error creating shader program!\n");
			exit(EXIT_FAILURE);
		}
		//shaders
		m_vertex_shader->setup(m_id);
		m_compute_shader->setup(m_id);
		m_geometry_shader->setup(m_id);
		m_fragment_shader->setup(m_id);
		m_tess_control_shader->setup(m_id);
		m_tess_evaluation_shader->setup(m_id);
		//link
		GLint status;
		GLchar log[1024];
		glLinkProgram(m_id);
		glGetProgramiv(m_id, GL_LINK_STATUS, &status);
		if(status == 0)
		{
			glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
			fprintf(stderr, "Error linking shader program: %s\n", log);
			exit(EXIT_FAILURE);
		}
		//validate
		glValidateProgram(m_id);
		glGetProgramiv(m_id, GL_VALIDATE_STATUS, &status);
		if(status == 0)
		{
			glGetProgramInfoLog(m_id, sizeof(log), nullptr, log);
			fprintf(stderr, "Error validating shader program: %s\n", log);
			exit(EXIT_FAILURE);
		}
	}
	void Program::bind(void) const
	{
		glUseProgram(m_id);
	}
	void Program::unbind(void)
	{
		glUseProgram(0);
	}

	//uniforms
	GLint Program::uniform_location(const char* name) const
	{
		//uniform
		GLint location = glGetUniformLocation(m_id, name);
		//check
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error getting uniform %s location!\n", name);
			exit(EXIT_FAILURE);
		}
		//return
		return location;
	}

	void Program::set_uniform(const char* name, float v0) const
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
	void Program::set_uniform(const char* name, float v0, float v1) const
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
	void Program::set_uniform(const char* name, float v0, float v1, float v2) const
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
	void Program::set_uniform(const char* name, float v0, float v1, float v2, float v3) const
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

	void Program::set_uniform(const char* name, int32_t v0) const
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
	void Program::set_uniform(const char* name, int32_t v0, int32_t v1) const
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
	void Program::set_uniform(const char* name, int32_t v0, int32_t v1, int32_t v2) const
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
	void Program::set_uniform(const char* name, int32_t v0, int32_t v1, int32_t v2, int32_t v3) const
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

	void Program::set_uniform(const char* name, uint32_t v0) const
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
	void Program::set_uniform(const char* name, uint32_t v0, uint32_t v1) const
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
	void Program::set_uniform(const char* name, uint32_t v0, uint32_t v1, uint32_t v2) const
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
	void Program::set_uniform(const char* name, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3) const
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

	void Program::set_uniform(const char* name, const float* data, uint32_t size) const
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
	void Program::set_uniform(const char* name, const int32_t* data, uint32_t size) const
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
	void Program::set_uniform(const char* name, const uint32_t* data, uint32_t size) const
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
	void Program::set_uniform_matrix(const char* name, const float* data, uint32_t size) const
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
	void Program::check_uniform(const char* name) const
	{
		if(glGetError() != GL_NO_ERROR)
		{
			printf("Error setting uniform %s!\n", name);
			exit(EXIT_FAILURE);
		}
	}
	void Program::check_uniform_location(const char* name, int32_t location) const
	{
		if(location == -1)
		{
			printf("Error getting uniform %s location!\n", name);
			exit(EXIT_FAILURE);
		}
	}
}