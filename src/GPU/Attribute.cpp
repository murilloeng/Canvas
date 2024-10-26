//ext
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/inc/GPU/Attribute.hpp"

namespace canvas
{
	//constructor
	Attribute::Attribute(uint32_t type, uint32_t size) : m_type(type), m_size(size)
	{
		return;
	}
	
	//destructor
	Attribute::~Attribute(void)
	{
		return;
	}

	//size
	uint32_t Attribute::bitsize(void) const
	{
		return 
			m_type == GL_INT ? m_size * sizeof(int32_t) :
			m_type == GL_BYTE ? m_size * sizeof(int8_t) :
			m_type == GL_FLOAT ? m_size * sizeof(float) :
			m_type == GL_UNSIGNED_INT ? m_size * sizeof(uint32_t) :
			m_type == GL_UNSIGNED_BYTE ? m_size * sizeof(uint8_t) : 0;
	}
}