//canvas
#include "Canvas/inc/Objects/Group.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Group::Group(void)
		{
			return;
		}

		//destructor
		Group::~Group(void)
		{
			return;
		}

		//data
		std::vector<Object*>& Group::objects(void)
		{
			return m_objects;
		}
		const std::vector<Object*>& Group::objects(void) const
		{
			return m_objects;
		}

		//setup
		void Group::setup(void)
		{
			Object::setup();
			for(uint32_t i = 0; i < m_vbo_size.size(); i++)
			{
				uint32_t offset = 0;
				for(Object* object : m_objects)
				{
					object->m_vbo_index[i] = m_vbo_index[i] + offset;
					offset += object->m_vbo_size[i];
				}
			}
			for(uint32_t i = 0; i < m_ibo_size.size(); i++)
			{
				uint32_t offset = 0;
				for(Object* object : m_objects)
				{
					object->m_ibo_index[i] = m_ibo_index[i] + offset;
					offset += object->m_ibo_size[i];
				}
			}
			for(Object* object : m_objects) object->m_scene = m_scene;
		}

		//buffers
		void Group::buffers_size(void)
		{
			for(Object* object : m_objects)
			{
				object->buffers_size();
			}
			for(uint32_t i = 0; i < m_vbo_size.size(); i++)
			{
				m_vbo_size[i] = 0;
				for(const Object* object : m_objects) m_vbo_size[i] += object->m_vbo_size[i];
			}
			for(uint32_t i = 0; i < m_ibo_size.size(); i++)
			{
				m_ibo_size[i] = 0;
				for(const Object* object : m_objects) m_ibo_size[i] += object->m_ibo_size[i];
			}
		}
		void Group::buffers_data(void) const
		{
			for(const Object* objects : m_objects) objects->buffers_data();
		}

		//model matrix
		void Group::apply_model_matrix(void) const
		{
			for(const Object* object : m_objects)
			{
				object->apply_model_matrix();
			}
			Object::apply_model_matrix();
		}
	}
}