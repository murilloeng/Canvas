#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Group.hpp"

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
			uint32_t mesh(uint32_t);
			uint32_t mesh(void) const;

			//arrows
			void add_arrow(float, bool);
			void remove_arrow(uint32_t);
			uint32_t arrows(void) const;
			Arrow* arrow(uint32_t) const;

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
			uint32_t vbo_size(uint32_t) const override;
			uint32_t ibo_size(uint32_t) const override;

			//buffers
			virtual void ibo_stroke_data(uint32_t**) const;
			virtual void vbo_stroke_data(vertices::Vertex**) const;

			void setup(uint32_t[], uint32_t[]) override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			uint32_t m_mesh;
		};
	}
}