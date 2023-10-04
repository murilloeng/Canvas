#pragma once

//std
#include <vector>

//canvas
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Group : public Object
		{
		public:
			//constructors
			Group(void);

			//destructor
			virtual ~Group(void);

			//data
			bool dot(bool);
			bool fill(bool);
			bool stroke(bool);

			void dot_color(const Color&);
			void dot_color(const Color&, unsigned);

			void fill_color(const Color&);
			void fill_color(const Color&, unsigned);

			void stroke_color(const Color&);
			void stroke_color(const Color&, unsigned);

		protected:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void vbo_affine(vertices::Vertex*) const;
			void buffers_index(unsigned&, unsigned[]) override;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			std::vector<Object*> m_objects;
		};
	}
}