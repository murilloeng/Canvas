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
			bool dot(bool) override;
			bool fill(bool) override;
			bool stroke(bool) override;

			Color color_dot(const Color&) override;
			Color color_fill(const Color&) override;
			Color color_stroke(const Color&) override;

		protected:
			//sizes
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//buffers
			void vbo_affine(vertices::Vertex*) const;
			void buffers_index(unsigned&, unsigned[]) override;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			std::vector<Object*> m_objects;
		};
	}
}