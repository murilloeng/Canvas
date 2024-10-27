//std
#include <cstring>

//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/GPU/IBO.hpp"

namespace canvas
{
	//constructor
	IBO::IBO(void) : m_size(0), m_data(nullptr)
	{
		glCreateBuffers(1, &m_id);
	}

	//destructor
	IBO::~IBO(void)
	{
		delete[] m_data;
		if(glIsBuffer(m_id)) glDeleteBuffers(1, &m_id);
	}

	//data
	uint32_t IBO::id(void) const
	{
		return m_id;
	}

	uint32_t IBO::size(void) const
	{
		return m_size;
	}
	uint32_t IBO::size(uint32_t size)
	{
		//data
		delete[] m_data;
		m_data = new uint32_t[size];
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
		//return
		return m_size = size;
	}
	
	uint32_t* IBO::data(void)
	{
		return m_data;
	}
	const uint32_t* IBO::data(void) const
	{
		return m_data;
	}
	uint32_t* IBO::data(const uint32_t* data)
	{
		return (uint32_t*) memcpy(m_data, data, m_size * sizeof(uint32_t));
	}

	//GPU
	void IBO::bind(void) const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}
	void IBO::unbind(void)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IBO::transfer(void) const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size * sizeof(uint32_t), m_data, GL_DYNAMIC_DRAW);
	}
}