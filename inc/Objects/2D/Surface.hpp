#pragma once

//std
#include <cstdint>
#include <functional>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Surface : public BaseModel3D
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
			//buffers data
			void ibo_data(uint32_t*) const;
			void vbo_data(vertices::Model3D*) const;

			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			float m_domain[4];
			uint32_t m_mesh[2];
			std::function<vec3(float, float)> m_position;
		};
	}
}