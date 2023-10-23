#pragma once

//std
#include <functional>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Surface : public Object
		{
		public:
			//constructors
			Surface(void);

			//destructor
			~Surface(void);

			//data
			unsigned mesh(unsigned) const;
			unsigned mesh(unsigned, unsigned);

			float domain(unsigned, unsigned) const;
			float domain(unsigned, unsigned, float);

			std::function<vec3(float, float)> position(void) const;
			std::function<vec3(float, float)> position(std::function<vec3(float, float)>);

		protected:
			//buffers
			unsigned vbo_size(unsigned) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_fill_data(unsigned**) const;
			void ibo_stroke_data(unsigned**) const;
			void vbo_fill_data(vertices::Vertex**) const;
			void vbo_stroke_data(vertices::Vertex**) const;
			void buffers_data(vertices::Vertex**, unsigned**) const override;

			//data
			float m_domain[4];
			unsigned m_mesh[2];
			std::function<vec3(float, float)> m_position;
		};
	}
}