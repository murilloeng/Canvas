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
		alt = 1 << 0, shift = 1 << 1, control = 1 << 2
	};
}

namespace canvas
{
	namespace cameras
	{
		class Click
		{
		private:
			//constructors
			Click(void);
	
			//destructor
			~Click(void);
	
			//data
			vec3 m_up;
			vec3 m_target;
			vec3 m_position;
			int32_t m_screen[2];
			uint32_t m_modifiers;
			canvas::button m_button;
	
			//friends
			friend class Camera;
		};
	}
}