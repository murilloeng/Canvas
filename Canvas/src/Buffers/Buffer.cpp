//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		Buffer::Buffer(void) : m_data{nullptr}, m_size{0}
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
			delete[] m_data;
			if(glIsBuffer(m_id)) glDeleteBuffers(1, &m_id);
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
		void Buffer::transfer(void) const
		{
			glNamedBufferData(m_id, m_size, m_data, GL_DYNAMIC_DRAW);
		}
		void Buffer::transfer(uint32_t offset, uint32_t size) const
		{
			glNamedBufferSubData(m_id, offset, size, m_data);
		}

		//data
		void Buffer::transfer(uint32_t size, const void* data)
		{
			m_size = size;
			delete[] m_data;
			m_data = new uint8_t[size];
			if(data) memcpy(m_data, data, size);
			glNamedBufferData(m_id, m_size, m_data, GL_DYNAMIC_DRAW);
		}
		void Buffer::transfer(uint32_t offset, uint32_t size, const void* data)
		{
			memcpy(m_data + offset, data, size);
			glNamedBufferSubData(m_id, offset, size, data);
		}
	}
}