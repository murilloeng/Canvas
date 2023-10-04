#pragma once

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Head : public Object
		{
		public:
			//constructors
			Head(void);

			//destructor
			~Head(void);

			//data
			float width(float);
			float width(void) const;

			float height(float);
			float height(void) const;

			unsigned mode(unsigned);
			unsigned mode(void) const;

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
			float m_width;
			float m_height;
			unsigned m_mode;
		};
	}
}