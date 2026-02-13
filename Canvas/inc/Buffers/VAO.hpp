#pragma once

//OpenGL
#include <GL/gl.h>

namespace canvas
{
	namespace buffers
	{
		class VAO
		{
		public:
			//constructor
			VAO(const char* = "");

			//destructor
			~VAO(void);

			//bind
			void bind(void) const;

			//data
			const char* label(void) const;
			const char* label(const char*);

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
			char m_label[64];
		};
	}
}