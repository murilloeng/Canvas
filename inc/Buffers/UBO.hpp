#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/inc/Buffers/Buffer.hpp"

namespace canvas
{
	namespace buffers
	{
		class UBO : public Buffer
		{
		public:
			//constructor
			UBO(void);

			//destructor
			virtual ~UBO(void);

			//bind
			void bind_base(GLuint) const;
		};
	}
}