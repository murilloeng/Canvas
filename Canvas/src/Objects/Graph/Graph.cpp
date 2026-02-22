//Canvas
#include "Canvas/Canvas/inc/Objects/Graph/Graph.hpp"

namespace canvas
{
	namespace objects
	{
		//constructor
		Graph::Graph(void) : m_font{0}, m_frame{this}
		{
			return;
		}

		//destructor
		Graph::~Graph(void)
		{
			return;
		}

		//data
		uint32_t Graph::font(void) const
		{
			return m_font;
		}
		uint32_t Graph::font(uint32_t font)
		{
			return m_font = font;
		}

		//draw
		void Graph::setup(void)
		{
			m_frame.setup();
		}
		void Graph::draw(void) const
		{
			m_frame.draw();
		}
	}
}