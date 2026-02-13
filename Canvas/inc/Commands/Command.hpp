#pragma once

//std
#include <cstdint>

//OpenGL
#include <GL/gl.h>

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
			Command(const char* = "");

			//destructor
			~Command(void);

			//data
			GLenum mode(GLenum);
			GLenum mode(void) const;

			const char* label(void) const;
			const char* label(const char*);

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
			char m_label[64];
			uint32_t m_vao_index;
			uint32_t m_shader_index;

			//friends
			friend class canvas::Scene;
		};
	}
}