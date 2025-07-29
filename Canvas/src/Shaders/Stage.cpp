//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"

namespace canvas
{
	//constructors
	Stage::Stage(GLenum type) : m_id(0), m_type(type)
	{
		return;
	}

	//destructor
	Stage::~Stage(void)
	{
		if(glIsShader(m_id)) glDeleteShader(m_id);
	}

	//data
	std::string Stage::path(void) const
	{
		return m_path;
	}
	std::string Stage::path(std::string path)
	{
		return m_path = path;
	}

	//setup
	void Stage::setup(GLuint shader_id)
	{
		//check
		if(m_path.empty())
		{
			if(m_type == GL_VERTEX_SHADER || m_type == GL_FRAGMENT_SHADER)
			{
				throw std::runtime_error(name() + std::string(" missing!"));
			}
			return;
		}
		//source
		if(!load_file())
		{
			throw std::runtime_error("Error loading shader source!");
		}
		//create
		if((m_id = glCreateShader(m_type)) == 0)
		{
			throw std::runtime_error("Shader creation failed!");
		}
		//source
		const GLchar* p = m_source.c_str();
		glShaderSource(m_id, 1, &p, nullptr);
		//compile
		GLint status;
		GLchar log[1024];
		glCompileShader(m_id);
		glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
		if(status == 0)
		{
			char error[4096];
			glGetShaderInfoLog(m_id, sizeof(log), nullptr, log);
			sprintf(error, "Shader compilation failed!\nSource: %s\n%s", m_path.c_str(), log);
			throw std::runtime_error(error);
		}
		//attach
		glAttachShader(shader_id, m_id);
	}
	bool Stage::load_file(void)
	{
		//open
		FILE* file = fopen(m_path.c_str(), "r");
		//check
		if(!file) return false;
		//read
		m_source.clear();
		while(!feof(file)) m_source += fgetc(file);
		m_source.back() = '\0';
		//close
		fclose(file);
		//return
		return true;
	}

	//name
	const char* Stage::name(void) const
	{
		return name(m_type);
	}
	const char* Stage::name(GLenum type)
	{
		if(type == GL_VERTEX_SHADER) return "Vertex Shader";
		else if(type == GL_COMPUTE_SHADER) return "Compute Shader";
		else if(type == GL_GEOMETRY_SHADER) return "Geometry Shader";
		else if(type == GL_FRAGMENT_SHADER) return "Fragment Shader";
		else if(type == GL_TESS_CONTROL_SHADER) return "Tesselation Control Shader";
		else if(type == GL_TESS_EVALUATION_SHADER) return "Tesselation Evaluation Shader";
		else return "Invalid shader type!";
	}
}