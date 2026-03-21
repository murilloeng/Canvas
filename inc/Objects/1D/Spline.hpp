#pragma once

//std
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Bases/BaseModel3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Spline : public BaseModel3D
		{
		public:
			//constructors
			Spline(void);

			//destructor
			~Spline(void);

			//data
			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

			vec3 point(uint32_t) const;
			vec3 point(uint32_t, const vec3&);

			vec3 control(uint32_t, uint32_t) const;
			vec3 control(uint32_t, uint32_t, const vec3&);

			void add_point(const vec3&);
			const std::vector<vec3>& points(void) const;
			const std::vector<vec3>& controls(void) const;

		protected:
			//draw
			void draw(void) override;
			void setup(void) override;
			void update(void) override;

			//data
			static uint32_t m_mesh;
			std::vector<vec3> m_points;
			std::vector<vec3> m_controls;
		};
	}
}