//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Function_2D.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Function_2D::Function_2D(void) : 
			m_samples(200), m_draw_color{0, 0, 0, 0}, m_fill_color{0, 0, 0, 0}, m_function([](double){ return 1; })
		{
			return;
		}

		//destructor
		Function_2D::~Function_2D(void)
		{
			return;
		}

		//data
		unsigned Function_2D::samples(void)
		{
			return m_samples;
		}
		unsigned Function_2D::samples(unsigned samples)
		{
			return m_samples = samples;
		}

		Color Function_2D::draw_color(void) const
		{
			return m_draw_color;
		}
		Color Function_2D::draw_color(Color draw_color)
		{
			return m_draw_color = draw_color;
		}

		Color Function_2D::fill_color(void) const
		{
			return m_fill_color;
		}
		Color Function_2D::fill_color(Color fill_color)
		{
			return m_fill_color = fill_color;
		}

		std::function<double(double)> Function_2D::function(void) const
		{
			return m_function;
		}
		std::function<double(double)> Function_2D::function(std::function<double(double)> function)
		{
			return m_function = function;
		}

		//type
		objects::type Function_2D::type(void) const
		{
			return objects::type::cylinder;
		}

		//buffers
		unsigned Function_2D::vbo_size(void) const
		{
			return 0;
		}
		unsigned Function_2D::ibo_size(unsigned index) const
		{
			return 0;
		}

		//draw
		void Function_2D::ibo_draw_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[1] + m_ibo_index[1];
		}
		void Function_2D::ibo_fill_data(unsigned** ibo_data) const
		{
			//data
			unsigned* ibo_ptr = ibo_data[2] + m_ibo_index[2];
		}
		void Function_2D::vbo_draw_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
		}
		void Function_2D::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			//data
			vertices::Model* vbo_ptr = (vertices::Model*) vbo_data + m_vbo_index;
		}
		void Function_2D::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_draw) vbo_draw_data(vbo_data);
			if(m_fill) vbo_fill_data(vbo_data);
			//ibo data
			if(m_draw) ibo_draw_data(ibo_data);
			if(m_fill) ibo_fill_data(ibo_data);
		}
	}
}