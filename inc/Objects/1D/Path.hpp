#pragma once

//std
#include <vector>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

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
		class Path : public Geometry
		{
		public:
			//constructors
			Path(void);

			//destructor
			~Path(void);

			//data
			uint32_t mesh(uint32_t);
			uint32_t mesh(void) const;

			//path
			vec3 path_normal(float) const;
			vec3 path_tangent(float) const;
			vec3 path_binormal(float) const;
			virtual float path_max(void) const;
			virtual vec3 path_hessian(float) const = 0;
			virtual vec3 path_position(float) const = 0;
			virtual vec3 path_gradient(float) const = 0;

		protected:
			//data
			virtual void ibo_stroke_data(uint32_t**) const;
			virtual void vbo_stroke_data(vertices::Vertex**) const;

			//buffers
			void buffers_size(void) override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			uint32_t m_mesh;

			//friends
			friend class Arrow;
		};
	}
}