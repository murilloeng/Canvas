#pragma once

//ext
#include "external/cpp/inc/GL/glew.h"

namespace canvas
{
	class Buffer
	{
	public:
		//constructors
		Buffer(void);
		Buffer(GLenum);

		//destructor
		~Buffer(void);

		//setup
		void setup(void);
		void bind(void) const;
		void unbind(void) const;
		void allocate(GLsizeiptr) const;
		void allocate(GLsizeiptr, void*) const;
		void read(GLsizeiptr, GLintptr, void*) const;
		void write(GLsizeiptr, GLintptr, void*) const;

	private:
		//data
		GLuint m_id;
		GLenum m_type;
	};
}