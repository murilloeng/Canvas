#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

namespace canvas
{
	class Scene;
	namespace cameras
	{
		class Camera;
	}
	namespace objects
	{
		class Object;
	}
}

namespace canvas
{
	namespace buffers
	{
		class VBO : public Buffer
		{
		public:
			//constructor
			VBO(bool);

			//destructor
			~VBO(void);

			//data
			char* data(void);
			const char* data(void) const;

			bool bounding_box(bool);
			bool bounding_box(void) const;

			uint32_t vertex_size(uint32_t);
			uint32_t vertex_size(void) const;

			uint32_t vertex_count(uint32_t);
			uint32_t vertex_count(void) const;

			//data
			void allocate(void);
			void transfer(void) const;
			void transfer(uint32_t, uint32_t) const;

		private:
			//data
			char* m_data;
			bool m_bounding_box;
			uint32_t m_vertex_size;
			uint32_t m_vertex_count;

			//friends
			friend class canvas::Scene;
			friend class canvas::objects::Object;
			friend class canvas::cameras::Camera;
		};
	}
}