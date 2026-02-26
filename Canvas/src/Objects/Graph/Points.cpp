//Canvas
#include "Canvas/Canvas/inc/Objects/Graph/Points.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructor
			Points::Points(void) : m_color{"white"}, m_size{5}, m_skip{1}, m_type{1}, m_enabled{true}
			{
				return;
			}
			
			//destructor
			Points::~Points(void)
			{
				return;
			}

			//data
			Color Points::color(void) const
			{
				return m_color;
			}
			Color Points::color(Color color)
			{
				return m_color = color;
			}

			uint32_t Points::size(void) const
			{
				return m_size;
			}
			uint32_t Points::size(uint32_t size)
			{
				return m_size = size;
			}
			
			uint32_t Points::skip(void) const
			{
				return m_skip;
			}
			uint32_t Points::skip(uint32_t skip)
			{
				return m_skip = skip;
			}

			uint32_t Points::type(void) const
			{
				return m_type;
			}
			uint32_t Points::type(uint32_t type)
			{
				return m_type = type;
			}

			uint32_t Points::enabled(void) const
			{
				return m_enabled;
			}
			uint32_t Points::enabled(bool enabled)
			{
				return m_enabled = enabled;
			}
		}
	}
}