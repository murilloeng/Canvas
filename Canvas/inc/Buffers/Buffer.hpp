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
			~Buffer(void);

			//data
			void transfer(void) const;
			void transfer(uint32_t, uint32_t) const;

			//data
			void transfer(uint32_t, const void*);
			void transfer(uint32_t, uint32_t, const void*);

		private:
			//data
			GLuint m_id;
			uint8_t* m_data;
			uint32_t m_size;
		};
	}
}