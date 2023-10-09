#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

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
		class Arrow : public Object
		{
		private:
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

			vec3 direction(unsigned) const;
			vec3 direction(unsigned, const vec3&);

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
			bool m_sense;
			vec3 m_point;
			float m_width;
			float m_height;
			float m_parameter;
			vec3 m_directions[2];
			//friends
			friend class Curve;
		};
	}
}