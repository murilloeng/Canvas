#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

namespace canvas
{
	namespace buffers
	{
		class SSBO : public Buffer
		{
		public:
			//constructor
			SSBO(void);

			//destructor
			virtual ~SSBO(void);

			//bind
			void bind_base(GLuint) const;
		};
	}
}