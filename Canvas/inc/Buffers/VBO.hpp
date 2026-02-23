#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

namespace canvas
{
	namespace buffers
	{
		class VBO : public Buffer
		{
		public:
			//constructor
			VBO(void);

			//destructor
			~VBO(void);

			//data
			char* data(void);
			const char* data(void) const;

			uint32_t vertex_size(uint32_t);
			uint32_t vertex_size(void) const;

			uint32_t vertex_count(uint32_t);
			uint32_t vertex_count(void) const;

			//data
			void allocate(void);
			void allocate(uint32_t);
			void transfer(void) const;
			void transfer(uint32_t, uint32_t) const;

		private:
			//data
			char* m_data;
			uint32_t m_vertex_size;
			uint32_t m_vertex_count;
		};
	}
}