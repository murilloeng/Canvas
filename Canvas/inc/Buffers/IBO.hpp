#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

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
	namespace buffers
	{
		class IBO : public Buffer
		{
		public:
			//constructor
			IBO(const char* = "");

			//destructor
			~IBO(void);

			//data
			uint32_t* data(void);
			const uint32_t* data(void) const;

			uint32_t vertex_count(uint32_t);
			uint32_t vertex_count(void) const;

			//data
			void allocate(void);
			void allocate(uint32_t);
			void transfer(void) const;
			void transfer(uint32_t, uint32_t) const;

		private:
			//data
			uint32_t* m_data;
			uint32_t m_vertex_count;

			//friends
			friend class canvas::Scene;
			friend class canvas::objects::Object;
		};
	}
}