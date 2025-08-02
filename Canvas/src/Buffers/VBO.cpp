//canvas
#include "Canvas/Canvas/inc/Buffers/VBO.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		VBO::VBO(void) : m_data{nullptr}, m_vertex_size{0}, m_vertex_count{0}
		{
			return;
		}

		//destructor
		VBO::~VBO(void)
		{
			delete[] m_data;
		}

		//data
		char* VBO::data(void)
		{
			return m_data;
		}
		const char* VBO::data(void) const
		{
			return m_data;
		}

		uint32_t VBO::vertex_size(void) const
		{
			return m_vertex_size;
		}
		uint32_t VBO::vertex_size(uint32_t vertex_size)
		{
			return m_vertex_size = vertex_size;
		}

		uint32_t VBO::vertex_count(void) const
		{
			return m_vertex_count;
		}
		uint32_t VBO::vertex_count(uint32_t vertex_count)
		{
			return m_vertex_count = vertex_count;
		}

		//data
		void VBO::allocate(void)
		{
			delete[] m_data;
			m_data = new char[m_vertex_size * m_vertex_count];
			glNamedBufferData(m_id, m_vertex_size * m_vertex_count, nullptr, GL_DYNAMIC_DRAW);
		}
		void VBO::transfer(void) const
		{
			glNamedBufferData(m_id, m_vertex_size * m_vertex_count, m_data, GL_DYNAMIC_DRAW);
		}
		void VBO::transfer(uint32_t offset, uint32_t size) const
		{
			const char* data = m_data + offset * m_vertex_size;
			glNamedBufferSubData(m_id, offset * m_vertex_size, size * m_vertex_size, data);
		}
	}
}