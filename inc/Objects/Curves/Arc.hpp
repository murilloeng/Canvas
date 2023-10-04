#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Curves/Curve.hpp"

namespace canvas
{
	namespace objects
	{
		class Arc : public Curve
		{
		public:
			//constructors
			Arc(void);

			//destructor
			~Arc(void);

			//data
			vec3 base(void) const;
			vec3 base(const vec3&);

			vec3 center(void) const;
			vec3 center(const vec3&);

			vec3 normal(void) const;
			vec3 normal(const vec3&);

			float radius(float);
			float radius(void) const;

			float angle(unsigned) const;
			float angle(unsigned, float);

			//path
			vec3 hessian(float) const override;
			vec3 position(float) const override;
			vec3 gradient(float) const override;

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void vbo_stroke_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			vec3 m_base;
			vec3 m_center;
			vec3 m_normal;
			float m_radius;
			float m_angles[2];
		};
	}
}