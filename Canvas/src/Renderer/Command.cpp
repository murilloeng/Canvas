//canvas
#include "Canvas/Canvas/inc/Renderer/Command.hpp"

namespace canvas
{
	//constructors
	Command::Command(uint32_t draw_mode, uint32_t vbo_index, uint32_t ibo_index, uint32_t texture_index, uint32_t program_index) : 
		m_mode(draw_mode), 
		m_vbo_index(vbo_index), 
		m_ibo_index(ibo_index), 
		m_texture_index(texture_index),
		m_program_index(program_index)
	{
		return;
	}

	//destructor
	Command::~Command(void)
	{
		return;
	}

	//data
	GLenum Command::mode(void) const
	{
		return m_mode;
	}
	GLenum Command::mode(GLenum mode)
	{
		return m_mode = mode;
	}

	uint32_t Command::vbo_index(void) const
	{
		return m_vbo_index;
	}
	uint32_t Command::vbo_index(uint32_t vbo_index)
	{
		return m_vbo_index = vbo_index;
	}

	uint32_t Command::ibo_index(void) const
	{
		return m_ibo_index;
	}
	uint32_t Command::ibo_index(uint32_t ibo_index)
	{
		return m_ibo_index = ibo_index;
	}

	uint32_t Command::program_index(void) const
	{
		return m_program_index;
	}
	uint32_t Command::program_index(uint32_t program_index)
	{
		return m_program_index = program_index;
	}

	//texture
	bool Command::has_texture(void) const
	{
		return m_texture_index != UINT32_MAX;
	}
}