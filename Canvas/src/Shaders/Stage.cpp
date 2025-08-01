//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Shaders/Stage.hpp"

namespace canvas
{
	namespace shaders
	{
		//constructors
		Stage::Stage(GLenum type, std::string path)
		{
			//create
			m_id = glCreateShader(type);
			//check
			if(!glIsShader(m_id))
			{
				throw std::runtime_error("Shader creation failed!");
			}
			//source
			read(path);
			const GLchar* p = m_source;
			glShaderSource(m_id, 1, &p, nullptr);
			//compile
			GLint status;
			GLchar log[4096];
			glCompileShader(m_id);
			glGetShaderiv(m_id, GL_COMPILE_STATUS, &status);
			if(status == 0)
			{
				char error[8192];
				glGetShaderInfoLog(m_id, sizeof(log), nullptr, log);
				sprintf(error, "Shader compilation failed!\nSource: %s\n%s", path.c_str(), log);
				throw std::runtime_error(error);
			}
		}
	
		//destructor
		Stage::~Stage(void)
		{
			if(glIsShader(m_id)) glDeleteShader(m_id);
		}
	
		//read
		void Stage::read(std::string path)
		{
			//open
			FILE* file = fopen(path.c_str(), "r");
			//check
			if(!file)
			{
				throw std::runtime_error("Failed to open shader file: " + std::string(path));
			}
			//read
			size_t position = fread(m_source, sizeof(char), sizeof(m_source) - 1, file);
			//null
			m_source[position] = '\0';
			//close
			fclose(file);
		}
	}
}