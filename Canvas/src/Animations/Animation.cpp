//canvas
#include "Canvas/Canvas/inc/Animations/Animation.hpp"

namespace canvas
{
	namespace animations
	{
		//constructor
		Animation::Animation(void) : 
			m_data{nullptr}, m_time_start{0.0f}, m_time_duration{1.0f}
		{
			return;
		}
	
		//constructor
		Animation::~Animation(void)
		{
			delete[] m_data;
		}

		//status
		bool Animation::status(float time) const
		{
			return time > m_time_start && time < m_time_start + m_time_duration;
		}
	}
}