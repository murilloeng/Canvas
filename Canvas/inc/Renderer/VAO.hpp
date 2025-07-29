#pragma once

//glew
#include "external/cpp/inc/GL/glew.h"

namespace canvas
{
	class VAO
	{
	public:
		//constructor
		VAO(void);

		//destructor
		~VAO(void);

		//bind
		void bind(void) const;

		//buffers
		void element_buffer(GLuint) const;
		void vertex_buffer(GLuint, GLuint, GLintptr, GLsizei) const;

		//attributes
		void attribute_enable(GLuint) const;
		void attribute_binding(GLuint, GLuint) const;
		void attribute_format(GLuint, GLuint, GLenum, GLuint) const;

	private:
		//data
		GLuint m_id;
	};
}