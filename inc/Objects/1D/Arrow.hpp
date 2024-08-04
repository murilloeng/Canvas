#pragma once

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

namespace canvas
{
	namespace objects
	{
		class Path;
	}
}

namespace canvas
{
	namespace objects
	{
		class Arrow : public Geometry
		{
		public:
			//constructors
			Arrow(void);

			//destructor
			~Arrow(void);

			//data
			Path* path(Path*);
			Path* path(void) const;

			bool sense(bool);
			bool sense(void) const;

			float width(float);
			float width(void) const;

			float height(float);
			float height(void) const;

			float parameter(float);
			float parameter(void) const;

		protected:
			//data
			void ibo_stroke_data(uint32_t**) const;
			void vbo_stroke_data(vertices::Vertex**) const;

			//buffers
			void setup(void) override;
			void buffers_size(void) override;
			void buffers_data(vertices::Vertex**, uint32_t**) const override;

			//data
			Path* m_path;
			bool m_sense;
			float m_width;
			float m_height;
			float m_parameter;
		};
	}
}