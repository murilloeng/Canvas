//std
#include <external/cpp/inc/GL/glew.h>

//canvas
#include "Canvas/inc/GPU/VBO.hpp"

namespace canvas
{
	//constructor
	VBO::VBO(void) : m_size(0), m_data(nullptr)
	{
		glCreateBuffers(1, &m_id);
		glCreateVertexArrays(1, &m_vao_id);
	}

	//destructor
	VBO::~VBO(void)
	{
		delete[] m_data;
		if(glIsBuffer(m_id)) glDeleteBuffers(1, &m_id);
		if(glIsVertexArray(m_vao_id)) glDeleteVertexArrays(1, &m_vao_id);
	}

	//data
	uint32_t VBO::size(void) const
	{
		return m_size;
	}
	uint32_t VBO::size(uint32_t size)
	{
		//data
		delete[] m_data;
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		m_data = (vertices::Vertex*) new int8_t[m_size * stride()];
		glBufferData(GL_ARRAY_BUFFER, size * stride(), nullptr, GL_DYNAMIC_DRAW);
		//return
		return m_size = size;
	}

	uint32_t VBO::id(void) const
	{
		return m_id;
	}
	uint32_t VBO::vao_id(void) const
	{
		return m_vao_id;
	}
	uint32_t VBO::stride(void) const
	{
		uint32_t stride = 0;
		for(const Attribute& attribute : m_attributes)
		{
			stride += attribute.bitsize();
		}
		return stride;
	}
	
	vertices::Vertex* VBO::data(void)
	{
		return m_data;
	}
	const vertices::Vertex* VBO::data(void) const
	{
		return m_data;
	}

	std::vector<Attribute>& VBO::attributes(void)
	{
		return m_attributes;
	}
	const std::vector<Attribute>& VBO::attributes(void) const
	{
		return m_attributes;
	}

	//GPU
	void VBO::bind(void) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}
	void VBO::unbind(void)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::enable(void) const
	{
		//bind
		glBindVertexArray(m_vao_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		//enable
		uint64_t offset = 0;
		const uint32_t stride = this->stride();
		for(uint32_t i = 0; i < m_attributes.size(); i++)
		{
			glEnableVertexAttribArray(i);
			const uint32_t size = m_attributes[i].m_size;
			const uint32_t type = m_attributes[i].m_type;
			glVertexAttribPointer(i, size, type, GL_FALSE, stride, (uint32_t*) offset);
			offset += m_attributes[i].bitsize();
		}
	}
	void VBO::transfer(void) const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, stride(), m_data, GL_DYNAMIC_DRAW);
	}
}