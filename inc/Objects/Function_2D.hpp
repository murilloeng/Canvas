#pragma once

//std
#include <functional>

//canvas
#include "inc/Colors/Color.hpp"
#include "inc/Objects/Object.hpp"

namespace canvas
{
	namespace objects
	{
		class Function_2D : public Object
		{
		public:
			//constructors
			Function_2D(void);

			//destructor
			~Function_2D(void);

			//data
			unsigned samples(void);
			unsigned samples(unsigned);

			Color draw_color(Color);
			Color draw_color(void) const;

			Color fill_color(Color);
			Color fill_color(void) const;

			std::function<double(double)> function(void) const;
			std::function<double(double)> function(std::function<double(double)>);

			//type
			objects::type type(void) const override;

		private:
			//buffers
			unsigned vbo_size(void) const override;
			unsigned ibo_size(unsigned) const override;

			//draw
			void ibo_draw_data(unsigned**) const;
			void ibo_fill_data(unsigned**) const;
			void vbo_draw_data(vertices::Vertex*) const;
			void vbo_fill_data(vertices::Vertex*) const;
			void buffers_data(vertices::Vertex*, unsigned**) const override;

			//data
			Color m_draw_color;
			Color m_fill_color;
			unsigned m_samples;
			float m_interval[2];
			std::function<double(double)> m_function;
		};
	}
}