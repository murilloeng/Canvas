//std
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/Renderer/VAO.hpp"

namespace canvas
{
	//constructor
	VAO::VAO(void)
	{
		glCreateVertexArrays(1, &m_id);
		if(!glIsVertexArray(m_id))
		{
			throw std::runtime_error("OpenGL vertex array creation failed!");
		}
	}

	//destructor
	VAO::~VAO(void)
	{
		return;
	}

	//bind
	void VAO::bind(void) const
	{
		glBindVertexArray(m_id);
	}

	//buffers
	void VAO::element_buffer(GLuint buffer) const
	{
		glVertexArrayElementBuffer(m_id, buffer);
	}
	void VAO::vertex_buffer(GLuint binding, GLuint buffer, GLintptr offset, GLsizei stride) const
	{
		glVertexArrayVertexBuffer(m_id, binding, buffer, offset, stride);
	}

	//attributes
	void VAO::attribute_enable(GLuint attribute) const
	{
		glEnableVertexArrayAttrib(m_id, attribute);
	}
	void VAO::attribute_binding(GLuint attribute, GLuint binding) const
	{
		glVertexArrayAttribBinding(m_id, attribute, binding);
	}
	void VAO::attribute_format(GLuint attribute, GLuint size, GLenum type, GLuint offset) const
	{
		glVertexArrayAttribFormat(m_id, attribute, size, type, GL_FALSE, offset);
	}
}