#pragma once

//std
#include <string>

//ext
#include "external/cpp/inc/GL/glew.h"

namespace canvas
{
	namespace shaders
	{
		class Shader;
	}
}

namespace canvas
{
	namespace shaders
	{
		class Stage
		{
		public:
			//constructors
			Stage(GLenum, std::string);

			//constructors
			~Stage(void);

		private:
			//read
			void read(std::string);

			//data
			GLuint m_id;
			char m_source[4096];

			//friends
			friend class Shader;
		};
	}
}