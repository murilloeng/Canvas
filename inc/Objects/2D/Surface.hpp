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
			//buffers
			void vbo_size(uint32_t[]) const override;
			void ibo_size(uint32_t[]) const override;

			//draw
			void ibo_fill_data(uint32_t**) const;
			void ibo_stroke_data(uint32_t**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			float m_domain[4];
			uint32_t m_mesh[2];
			std::function<vec3(float, float)> m_position;
		};
	}
}