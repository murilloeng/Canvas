#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/inc/GPU/Attribute.hpp"
#include "Canvas/inc/Vertices/Vertex.hpp"

namespace canvas
{
	class Scene;
	namespace objects
	{
		class Object;
	}
}

namespace canvas
{
	class VBO
	{
	public:
		//constructor
		VBO(void);

		//destructor
		~VBO(void);

		//data
		uint32_t size(uint32_t);
		uint32_t size(void) const;

		uint32_t id(void) const;
		uint32_t vao_id(void) const;
		uint32_t stride(void) const;

		void* data(void);
		const void* data(void) const;

		std::vector<Attribute>& attributes(void);
		const std::vector<Attribute>& attributes(void) const;

		//GPU
		void allocate(void);
		void bind(void) const;
		void enable(void) const;
		void transfer(void) const;

	private:
		//data
		void* m_data;
		uint32_t m_id;
		uint32_t m_size;
		uint32_t m_vao_id;
		std::vector<Attribute> m_attributes;

		//friends
		friend class Scene;
		friend class objects::Object;
	};
}