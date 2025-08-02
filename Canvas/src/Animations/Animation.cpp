//canvas
#include "Canvas/Canvas/inc/Animations/Animation.hpp"

namespace canvas
{
	namespace animations
	{
		//constructor
		Animation::Animation(void) : m_status{false}, m_time_start{0.0f}, m_time_duration{1.0f}
		{
			return;
		}
	
		//constructor
		Animation::~Animation(void)
		{
			return;
		}

		//data
		bool Animation::status(void) const
		{
			return m_status;
		}

		float Animation::time_start(void) const
		{
			return m_time_start;
		}
		float Animation::time_start(float time_start)
		{
			return m_time_start = time_start;
		}

		float Animation::time_durantion(void) const
		{
			return m_time_duration;
		}
		float Animation::time_durantion(float time_durantion)
		{
			return m_time_duration = time_durantion;
		}

		Easing& Animation::easing(void)
		{
			return m_easing;
		}
		const Easing& Animation::easing(void) const
		{
			return m_easing;
		}

		//update
		void Animation::setup(void)
		{
			m_status = true;
		}
		void Animation::cleanup(void)
		{
			m_status = false;
		}
		void Animation::animate(float)
		{
			if(!m_status) setup();
		}
	}
}