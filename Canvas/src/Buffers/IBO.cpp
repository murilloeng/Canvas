//canvas
#include "Canvas/Canvas/inc/API/API.hpp"
#include "Canvas/Canvas/inc/Buffers/IBO.hpp"

namespace canvas
{
	namespace buffers
	{
		//constructor
		IBO::IBO(void) : m_data{nullptr}, m_vertex_count{0}
		{
			return;
		}

		//destructor
		IBO::~IBO(void)
		{
			delete[] m_data;
		}

		//data
		uint32_t* IBO::data(void)
		{
			return m_data;
		}
		const uint32_t* IBO::data(void) const
		{
			return m_data;
		}

		uint32_t IBO::vertex_count(void) const
		{
			return m_vertex_count;
		}
		uint32_t IBO::vertex_count(uint32_t vertex_count)
		{
			return m_vertex_count = vertex_count;
		}

		//data
		void IBO::allocate(void)
		{
			delete[] m_data;
			m_data = new uint32_t[m_vertex_count];
			glNamedBufferData(m_id, m_vertex_count * sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
		}
		void IBO::transfer(void) const
		{
			glNamedBufferData(m_id, m_vertex_count * sizeof(uint32_t), m_data, GL_DYNAMIC_DRAW);
		}
		void IBO::transfer(uint32_t offset, uint32_t size) const
		{
			const uint32_t* data = m_data + offset;
			glNamedBufferSubData(m_id, offset * sizeof(uint32_t), size * sizeof(uint32_t), data);
		}
	}
}