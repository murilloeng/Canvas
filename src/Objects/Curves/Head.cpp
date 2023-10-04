//std
#include <cmath>

//canvas
#include "inc/Vertices/Model.hpp"

#include "inc/Objects/Type.hpp"
#include "inc/Objects/Curves/Head.hpp"

namespace canvas
{
	namespace objects
	{
		//constructors
		Head::Head(void) : m_width(0), m_height(0), m_mode(0)
		{
			m_fill_colors.resize(1);
			m_stroke_colors.resize(1);
		}

		//destructor
		Head::~Head(void)
		{
			return;
		}

		//data
		float Head::width(void) const
		{
			return m_width;
		}
		float Head::width(float width)
		{
			return m_width = width;
		}

		float Head::height(void) const
		{
			return m_height;
		}
		float Head::height(float height)
		{
			return m_height = height;
		}

		unsigned Head::mode(void) const
		{
			return m_mode;
		}
		unsigned Head::mode(unsigned mode)
		{
			return m_mode = mode;
		}

		//type
		objects::type Head::type(void) const
		{
			return objects::type::head;
		}

		//buffers
		unsigned Head::vbo_size(void) const
		{
			return 0;
		}
		unsigned Head::ibo_size(unsigned index) const
		{
			return 0;
		}

		//draw
		void Head::ibo_fill_data(unsigned** ibo_data) const
		{
			return;
		}
		void Head::ibo_stroke_data(unsigned** ibo_data) const
		{
			return;
		}
		void Head::vbo_fill_data(vertices::Vertex* vbo_data) const
		{
			return;
		}
		void Head::vbo_stroke_data(vertices::Vertex* vbo_data) const
		{
			return;
		}
		void Head::buffers_data(vertices::Vertex* vbo_data, unsigned** ibo_data) const
		{
			//vbo data
			if(m_fill) vbo_fill_data(vbo_data);
			if(m_stroke) vbo_stroke_data(vbo_data);
			//ibo data
			if(m_fill) ibo_fill_data(ibo_data);
			if(m_stroke) ibo_stroke_data(ibo_data);
		}
	}
}