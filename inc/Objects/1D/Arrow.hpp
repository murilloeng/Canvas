#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Curve;
	}
}

namespace canvas
{
	namespace objects
	{
		class Arrow : public Geometry
		{
		protected:
			//constructors
			Arrow(void);

			//destructor
			~Arrow(void);

		public:
			//data
			bool sense(bool);
			bool sense(void) const;

			vec3 point(void) const;
			vec3 point(const vec3&);

			float width(float);
			float width(void) const;

			float height(float);
			float height(void) const;

			float parameter(float);
			float parameter(void) const;

			vec3 direction(uint32_t) const;
			vec3 direction(uint32_t, const vec3&);

		protected:
			//buffers
			uint32_t vbo_size(uint32_t) const override;
			uint32_t ibo_size(uint32_t) const override;

			//draw
			void ibo_stroke_data(uint32_t**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			bool m_sense;
			vec3 m_point;
			float m_width;
			float m_height;
			float m_parameter;
			vec3 m_directions[2];
			//friends
			friend class Path;
		};
	}
}