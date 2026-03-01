//Canvas
#include "Canvas/Canvas/inc/Objects/Graph/Axis.hpp"

namespace canvas
{
	namespace objects
	{
		namespace graphs
		{
			//constructor
			Axis::Axis(void) : 
				m_range{-1.0f, +1.0f}, m_font_size{0.05f}, m_ticks_size{0.05f}, m_label{"Axis"}, m_format{"%+.2f"}, m_ticks_count{11}
			{
				return;
			}

			//destructor
			Axis::~Axis(void)
			{
				return;
			}

			//data
			float Axis::font_size(void) const
			{
				return m_font_size;
			}
			float Axis::font_size(uint32_t font_size)
			{
				return m_font_size = font_size;
			}

			float Axis::ticks_size(void) const
			{
				return m_ticks_size;
			}
			float Axis::ticks_size(float ticks_size)
			{
				return m_ticks_size = ticks_size;
			}

			float Axis::range(uint32_t index) const
			{
				return m_range[index];
			}
			float Axis::range(uint32_t index, float range)
			{
				return m_range[index] = range;
			}

			std::string Axis::label(void) const
			{
				return m_label;
			}
			std::string Axis::label(std::string label)
			{
				return m_label = label;
			}

			const std::string& Axis::format(void) const
			{
				return m_format;
			}
			std::string Axis::format(std::string format)
			{
				return m_format = format;
			}

			uint32_t Axis::ticks_count(void) const
			{
				return m_ticks_count;
			}
			uint32_t Axis::ticks_count(uint32_t ticks_count)
			{
				return m_ticks_count = ticks_count;
			}
		}
	}
}