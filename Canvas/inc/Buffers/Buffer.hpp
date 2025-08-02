#pragma once

//std
#include <cstdint>

//glew
#include "external/cpp/inc/GL/glew.h"

namespace canvas
{
	namespace buffers
	{
		class Buffer
		{
		public:
			//constructor
			Buffer(void);

			//destructor
			virtual ~Buffer(void);

			//data
			GLuint id(void) const;

			//bind
			void bind(GLenum) const;

			//transfer
			void transfer(uint32_t, const void*);
			void transfer(uint32_t, uint32_t, const void*);

		protected:
			//data
			GLuint m_id;
		};
	}
}