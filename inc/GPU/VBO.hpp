#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/inc/GPU/Attribute.hpp"
#include "Canvas/inc/Vertices/Vertex.hpp"

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

		vertices::Vertex* data(void);
		const vertices::Vertex* data(void) const;

		std::vector<Attribute>& attributes(void);
		const std::vector<Attribute>& attributes(void) const;

		//GPU
		void setup(void);

		void bind(void) const;
		static void unbind(void);

		void enable(void) const;
		void transfer(void) const;

	private:
		//data
		uint32_t m_id;
		uint32_t m_size;
		uint32_t m_vao_id;
		vertices::Vertex* m_data;
		std::vector<Attribute> m_attributes;
	};
}