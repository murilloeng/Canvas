#pragma once

//std
#include <cstdint>

//glew
#include "external/cpp/inc/GL/glew.h"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace commands
	{
		class Command
		{
		public:
			//constructor
			Command(void);
	
			//destructor
			~Command(void);
	
			//data
			GLenum mode(GLenum);
			GLenum mode(void) const;
	
			uint32_t vao_index(uint32_t);
			uint32_t vao_index(void) const;
	
			uint32_t shader_index(uint32_t);
			uint32_t shader_index(void) const;

			void setup(GLenum, uint32_t, uint32_t);
	
		private:
			//draw
			void draw(const Scene*) const;
	
			//data
			GLenum m_mode;
			uint32_t m_vao_index;
			uint32_t m_shader_index;
	
			//friends
			friend class Scene;
		};
	}
}