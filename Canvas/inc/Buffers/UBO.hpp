#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

namespace canvas
{
	namespace buffers
	{
		class UBO : public Buffer
		{
		public:
			//constructor
			UBO(const char* = "");

			//destructor
			virtual ~UBO(void);

			//bind
			void bind_base(GLenum, GLuint) const;
		};
	}
}