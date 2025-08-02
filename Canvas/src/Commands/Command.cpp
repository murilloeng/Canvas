//canvas
#include "Canvas/Canvas/inc/Buffers/VAO.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Commands/Command.hpp"

namespace canvas
{
	namespace commands
	{
		//constructors
		Command::Command(void) : 
			m_mode{GL_POINTS}, m_vao_index{0}, m_shader_index{0}
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

		uint32_t Command::vao_index(void) const
		{
			return m_vao_index;
		}
		uint32_t Command::vao_index(uint32_t vbo_index)
		{
			return m_vao_index = vbo_index;
		}

		uint32_t Command::shader_index(void) const
		{
			return m_shader_index;
		}
		uint32_t Command::shader_index(uint32_t shader_index)
		{
			return m_shader_index = shader_index;
		}

		void Command::setup(GLenum mode, uint32_t vao_index, uint32_t shader_index)
		{
			m_mode = mode;
			m_vao_index = vao_index;
			m_shader_index = shader_index;
		}

		//draw
		void Command::draw(const Scene* scene) const
		{
			//setup
			GLint size;
			scene->vao(m_vao_index)->bind();
			scene->shader(m_shader_index)->bind();
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			//draw
			glDrawElements(m_mode, size / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
		}
	}
}