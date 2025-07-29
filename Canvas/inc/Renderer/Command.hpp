#pragma once

//std
#include <cstdint>

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
		uint32_t draw_mode(uint32_t);
		uint32_t draw_mode(void) const;

		uint32_t vbo_index(uint32_t);
		uint32_t vbo_index(void) const;

		uint32_t ibo_index(uint32_t);
		uint32_t ibo_index(void) const;

		uint32_t program_index(uint32_t);
		uint32_t program_index(void) const;

		//texture
		bool has_texture(void) const;

private:
		//data
		uint32_t m_draw_mode;
		uint32_t m_vbo_index;
		uint32_t m_ibo_index;
		uint32_t m_texture_index;
		uint32_t m_program_index;

		//friends
		friend class Scene;
	};
}