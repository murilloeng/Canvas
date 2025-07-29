#pragma once

//std
#include <cstdint>

//glew
#include "external/cpp/inc/GL/glew.h"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	class Command
	{
	public:
		//constructor
		Command(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

		//destructor
		~Command(void);

		//data
		GLenum mode(GLenum);
		GLenum mode(void) const;

		uint32_t vbo_index(uint32_t);
		uint32_t vbo_index(void) const;

		uint32_t ibo_index(uint32_t);
		uint32_t ibo_index(void) const;

		uint32_t program_index(uint32_t);
		uint32_t program_index(void) const;

		//texture
		bool has_texture(void) const;

	private:
		//draw
		void draw(void) const;

		//data
		GLenum m_mode;
		uint32_t m_vao_index;
		uint32_t m_vbo_index;
		uint32_t m_ibo_index;
		uint32_t m_texture_index;
		uint32_t m_program_index;

		//friends
		friend class Scene;
	};
}