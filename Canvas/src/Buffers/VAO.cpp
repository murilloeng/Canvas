//std
#include <cstring>
#include <stdexcept>

//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		VAO::VAO(const char* label)
		{
			//create
			strcpy(m_label, label);
			glCreateVertexArrays(1, &m_id);
			//check
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

		//data
		const char* VAO::label(void) const
		{
			return m_label;
		}
		const char* VAO::label(const char* label)
		{
			return strcpy(m_label, label);
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
}