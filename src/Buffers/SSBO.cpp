//canvas
#include "Canvas/inc/API/API.hpp"
#include "Canvas/inc/Buffers/SSBO.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		SSBO::SSBO(void)
		{
			return;
		}

		//destructor
		SSBO::~SSBO(void)
		{
			return;
		}

		//bind
		void SSBO::bind_base(GLuint index) const
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, m_id);
		}
	}
}