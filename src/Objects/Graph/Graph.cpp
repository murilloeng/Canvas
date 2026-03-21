//Canvas
#include "Canvas/inc/Objects/Graph/Graph.hpp"

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

		graphs::Frame& Graph::frame(void)
		{
			return m_frame;
		}
		const graphs::Frame& Graph::frame(void) const
		{
			return m_frame;
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
		void Graph::draw(void)
		{
			m_frame.draw();
			for(graphs::Curve* curve : m_curves) curve->draw();
		}
		void Graph::setup(void)
		{
			m_frame.setup();
			for(graphs::Curve* curve : m_curves)
			{
				curve->m_frame = &m_frame;
				curve->setup();
			}
		}
		void Graph::update(void)
		{
			m_frame.update();
			for(graphs::Curve* curve : m_curves) curve->update();
		}
	}
}