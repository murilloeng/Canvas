//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		Buffer::Buffer(void)
		{
			//create
			glCreateBuffers(1, &m_id);
			//check
			if(!glIsBuffer(m_id))
			{
				throw std::runtime_error("OpenGL buffer creation failed!");
			}
		}

		//destructor
		Buffer::~Buffer(void)
		{
			if(glIsBuffer(m_id)) glDeleteBuffers(1, &m_id);
		}

		//data
		GLuint Buffer::id(void) const
		{
			return m_id;
		}

		//bind
		void Buffer::bind(GLenum target) const
		{
			glBindBuffer(target, m_id);
		}
		void Buffer::bind_base(GLenum target, GLuint index) const
		{
			glBindBufferBase(target, index, m_id);
		}

		//data
		void Buffer::transfer(uint32_t size, const void* data)
		{
			glNamedBufferData(m_id, size, data, GL_DYNAMIC_DRAW);
		}
		void Buffer::transfer(uint32_t offset, uint32_t size, const void* data)
		{
			glNamedBufferSubData(m_id, offset, size, data);
		}
	}
}