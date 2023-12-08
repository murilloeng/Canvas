#pragma once

//std
#include <vector>

//canvas
#include "Canvas/lib/inc/Math/vec3.hpp"
#include "Canvas/lib/inc/Objects/Group.hpp"

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
		class Path : public Group
		{
		public:
			//constructors
			Path(void);

			//destructor
			~Path(void);

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
			virtual float path_max(void) const;
			virtual vec3 path_hessian(float) const = 0;
			virtual vec3 path_position(float) const = 0;
			virtual vec3 path_gradient(float) const = 0;

		protected:
			//sizes
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//buffers
			virtual void ibo_stroke_data(unsigned**) const;
			virtual void vbo_stroke_data(vertices::Vertex**) const;

			void setup(unsigned[], unsigned[]) override;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			unsigned m_mesh;
		};
	}
}