//canvas
#include "Canvas/inc/API/API.hpp"
#include "Canvas/inc/Buffers/UBO.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		UBO::UBO(void)
		{
			return;
		}

		//destructor
		UBO::~UBO(void)
		{
			return;
		}

		//bind
		void UBO::bind_base(GLuint index) const
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, index, m_id);
		}
	}
}