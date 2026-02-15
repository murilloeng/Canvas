#pragma once

//std
#include <vector>

//Canvas
#include "Canvas/Canvas/inc/Objects/Model3D.hpp"

namespace canvas
{
	namespace objects
	{
		class Bezier : public Model3D
		{
		public:
			//constructor
			Bezier(void);

			//destructor
			~Bezier(void);

			//types
			enum class Type : uint32_t {Conic, Cubic};

			//data
			Type type(Type);
			Type type(void) const;

			vec3 point(uint32_t, vec3);
			vec3 point(uint32_t) const;

			vec3 control(uint32_t, vec3);
			vec3 control(uint32_t) const;

			static uint32_t mesh(void);
			static uint32_t mesh(uint32_t);

		private:
			//draw
			void setup(void) override;
			void draw(void) const override;

			//data
			Type m_type;
			vec3 m_points[2];
			vec3 m_controls[2];
			static uint32_t m_mesh;
		};
	}
}