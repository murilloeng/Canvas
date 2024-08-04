#pragma once

//std
#include <functional>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Surface : public Geometry
		{
		public:
			//constructors
			Surface(void);

			//destructor
			~Surface(void);

			//data
			uint32_t mesh(uint32_t) const;
			uint32_t mesh(uint32_t, uint32_t);

			float domain(uint32_t, uint32_t) const;
			float domain(uint32_t, uint32_t, float);

			std::function<vec3(float, float)> position(void) const;
			std::function<vec3(float, float)> position(std::function<vec3(float, float)>);

		protected:
			//data
			void ibo_fill_data(void) const;
			void vbo_fill_data(void) const;
			void ibo_stroke_data(void) const;
			void vbo_stroke_data(void) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			float m_domain[4];
			uint32_t m_mesh[2];
			std::function<vec3(float, float)> m_position;
		};
	}
}