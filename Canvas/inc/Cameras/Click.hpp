#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/quat.hpp"

namespace canvas
{
	namespace cameras
	{
		class Camera;
	}
	enum class key : uint32_t
	{
		left, right, down, up
	};
	enum class button : uint32_t
	{
		none, left, middle, right
	};
	enum class modifier : uint32_t
	{
		alt, ctrl, shift
	};
}

namespace canvas
{
	namespace cameras
	{
		class Click
		{
		public:
			//constructors
			Click(void);
	
			//destructor
			~Click(void);
	
		protected:
			//data
			vec3 m_up;
			vec3 m_target;
			vec3 m_position;
			int32_t m_screen[2];
			canvas::button m_button;
	
			//friends
			friend class Camera;
		};
	}
}