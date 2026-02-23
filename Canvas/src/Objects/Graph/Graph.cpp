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
			for(const graphs::Curve* curve : m_curves) delete curve;
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

		std::vector<graphs::Curve*>& Graph::curves(void)
		{
			return m_curves;
		}
		const std::vector<graphs::Curve*>& Graph::curves(void) const
		{
			return m_curves;
		}

		//draw
		void Graph::setup(void)
		{
			m_frame.setup();
			for(graphs::Curve* curve : m_curves) curve->setup();
		}
		void Graph::draw(void) const
		{
			m_frame.draw();
			for(const graphs::Curve* curve : m_curves) curve->draw();
		}
	}
}