//std
#include <stdexcept>

//canvas
#include "Canvas/inc/API/API.hpp"
#include "Canvas/inc/Buffers/VAO.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		VAO::VAO(void)
		{
			//create
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
		void VAO::binding_divisor(GLuint binding, GLuint divisor) const
		{
			glVertexArrayBindingDivisor(m_id, binding, divisor);
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
		void VAO::attribute_format_double(GLuint attribute, GLuint size, GLenum type, GLuint offset) const
		{
			glVertexArrayAttribLFormat(m_id, attribute, size, type, offset);
		}
		void VAO::attribute_format_integer(GLuint attribute, GLuint size, GLenum type, GLuint offset) const
		{
			glVertexArrayAttribIFormat(m_id, attribute, size, type, offset);
		}
	}
}