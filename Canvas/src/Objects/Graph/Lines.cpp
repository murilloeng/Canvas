//Canvas
#include "Canvas/Canvas/inc/Objects/Graph/Lines.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructor
			Lines::Lines(void) : m_color{"white"}, m_width{1}, m_enabled{true}, m_dash_size{10}, m_dash_type{1}
			{
				return;
			}
			
			//destructor
			Lines::~Lines(void)
			{
				return;
			}

			//data
			Color Lines::color(void) const
			{
				return m_color;
			}
			Color Lines::color(Color color)
			{
				return m_color = color;
			}

			uint32_t Lines::width(void) const
			{
				return m_width;
			}
			uint32_t Lines::width(uint32_t width)
			{
				return m_width = width;
			}

			uint32_t Lines::enabled(void) const
			{
				return m_enabled;
			}
			uint32_t Lines::enabled(bool enabled)
			{
				return m_enabled = enabled;
			}

			uint32_t Lines::dash_size(void) const
			{
				return m_dash_size;
			}
			uint32_t Lines::dash_size(uint32_t dash_size)
			{
				return m_dash_size = dash_size;
			}

			uint32_t Lines::dash_type(void) const
			{
				return m_dash_type;
			}
			uint32_t Lines::dash_type(uint32_t dash_type)
			{
				return m_dash_type = dash_type;
			}
		}
	}
}