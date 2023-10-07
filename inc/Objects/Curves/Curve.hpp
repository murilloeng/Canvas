#pragma once

//std
#include <vector>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Group.hpp"

namespace canvas
{
	namespace objects
	{
		class Arrow;
	}
}

namespace canvas
{
	namespace objects
	{
		class Curve : public Group
		{
		public:
			//constructors
			Curve(void);

			//destructor
			~Curve(void);

			//data
			unsigned mesh(unsigned);
			unsigned mesh(void) const;

			//arrows
			void add_arrow(float, bool);
			void remove_arrow(unsigned);
			unsigned arrows(void) const;
			Arrow* arrow(unsigned) const;

			//path
			vec3 path_normal(float) const;
			vec3 path_tangent(float) const;
			vec3 path_binormal(float) const;
			virtual vec3 path_hessian(float) const = 0;
			virtual vec3 path_position(float) const = 0;
			virtual vec3 path_gradient(float) const = 0;

		protected:
			//buffers
			void buffers_index(unsigned&, unsigned[]) override;

			//data
			unsigned m_mesh;
		};
	}
}