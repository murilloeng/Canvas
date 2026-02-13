//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Buffers/UBO.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		UBO::UBO(const char* label) : Buffer(label)
		{
			return;
		}

		//destructor
		UBO::~UBO(void)
		{
			return;
		}

		//bind
		void UBO::bind_base(GLenum target, GLuint index) const
		{
			glBindBufferBase(target, index, m_id);
		}
	}
}