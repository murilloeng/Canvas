#pragma once

//std
#include <string>

//ext
#include "external/cpp/inc/GL/glew.h"

namespace canvas
{
	class Stage
	{
	public:
		//constructors
		Stage(GLenum);

		//constructors
		~Stage(void);

		//data
		std::string path(void) const;
		std::string path(std::string);

		//setup
		void setup(GLuint);
		bool load_file(void);

		//name
		const char* name(void) const;
		static const char* name(GLenum);

	private:
		//data
		GLuint m_id;
		GLenum m_type;
		std::string m_path;
		std::string m_source;
	};
}