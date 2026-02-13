#pragma once

//std
#include <cstdint>

//OpenGL
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>

namespace canvas
{
	namespace buffers
	{
		class Buffer
		{
		public:
			//constructor
			Buffer(const char* = "");

			//destructor
			virtual ~Buffer(void);

			//bind
			void bind(GLenum) const;

			//data
			GLuint id(void) const;

			const char* label(void) const;
			const char* label(const char*);

			//transfer
			void transfer(uint32_t, const void*);
			void transfer(uint32_t, uint32_t, const void*);

		protected:
			//data
			GLuint m_id;
			char m_label[64];
		};
	}
}