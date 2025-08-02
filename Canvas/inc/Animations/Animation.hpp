#pragma once

//canvas
#include "Canvas/Canvas/inc/Animations/Easing.hpp"

namespace canvas
{
	namespace cameras
	{
		class Camera;
	}
	namespace objects
	{
		class Object;
	}
	namespace animations
	{
		enum class type : uint32_t
		{
			shift, rotate
		};
	}
}

namespace canvas
{
	namespace animations
	{
		class Animation
		{
		public:
			//constructor
			Animation(void);

			//destructor
			~Animation(void);

			//status
			bool status(float) const;

		private:
			//data
			uint8_t* m_data;
			Easing m_easing;
			float m_time_start;
			float m_time_duration;

			//friends
			friend class cameras::Camera;
			friend class objects::Object;
		};
	}
}