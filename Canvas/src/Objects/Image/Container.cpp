//canvas
#include "Canvas/Canvas/inc/Objects/Image/Container.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Container::Container(void) : m_object{nullptr}
		{
			return;
		}
		
		//destructor
		Container::~Container(void)
		{
			return;
		}

		//setup
		void Container::setup(void)
		{
			Object::setup();
			m_object->m_scene = m_scene;
			for(uint32_t i = 0; i < m_vbo_size.size(); i++)
			{
				m_object->m_vbo_index[i] = m_vbo_index[i];
			}
			for(uint32_t i = 0; i < m_ibo_size.size(); i++)
			{
				m_object->m_ibo_index[i] = m_ibo_index[i];
			}
		}

		//buffers
		void Container::buffers_size(void)
		{
			if(m_object) m_object->buffers_size();
		}
		void Container::buffers_data(void) const
		{

		}
	}
}