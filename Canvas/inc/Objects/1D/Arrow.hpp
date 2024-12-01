#pragma once

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Objects/Geometry.hpp"

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
			//buffers
			void setup(void) override;
			void buffers_size(void) override;
			void buffers_data(void) const override;

			//data
			Path* m_path;
			bool m_sense;
			float m_width;
			float m_height;
			float m_parameter;
		};
	}
}