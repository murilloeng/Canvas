#pragma once

//std
#include <cstdint>
#include <functional>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Curve : public Model3D
		{
		public:
			//constructors
			Curve(void);

			//destructor
			~Curve(void);

			//data
			uint32_t mesh(uint32_t);
			uint32_t mesh(void) const;

			float domain(uint32_t) const;
			float domain(uint32_t, float);

			std::function<vec3(float)> position(void) const;
			std::function<vec3(float)> position(std::function<vec3(float)>);

		protected:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			uint32_t m_mesh;
			float m_domain[2];
			std::function<vec3(float)> m_position;
		};
	}
}