//canvas
#include "Canvas/inc/GPU/Buffer.hpp"

namespace canvas
{
	//constructors
	Buffer::Buffer(void) : m_id(0), m_type(0)
	{
		return;
	}
	Buffer::Buffer(GLenum type) : m_id(0), m_type(type)
	{
		return;
	}
	
	//destructor
	Buffer::~Buffer(void)
	{
		if(glIsBuffer(m_id)) glDeleteBuffers(1, &m_id);
	}

	//setup
	void Buffer::setup(void)
	{
		glGenBuffers(1, &m_id);
	}
	void Buffer::bind(void) const
	{
		glBindBuffer(m_type, m_id);
	}
	void Buffer::unbind(void) const
	{
		glBindBuffer(m_type, 0);
	}
	void Buffer::allocate(GLsizeiptr size) const
	{
		glBufferData(m_type, size, nullptr, GL_DYNAMIC_DRAW);
	}
	void Buffer::allocate(GLsizeiptr size, void* data) const
	{
		glBufferData(m_type, size, data, GL_DYNAMIC_DRAW);
	}
	void Buffer::read(GLsizeiptr size, GLintptr offset, void* data) const
	{
		glGetBufferSubData(m_type, offset, size, data);
	}
	void Buffer::write(GLsizeiptr size, GLintptr offset, void* data) const
	{
		glBufferSubData(m_type, offset, size, data);
	}
}