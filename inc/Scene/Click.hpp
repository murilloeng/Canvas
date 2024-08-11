#pragma once

//std
#include <cstdint>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Math/quat.hpp"

namespace canvas
{
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
	class Click
	{
	public:
		//constructors
		Click(void);

		//destructor
		~Click(void);

		//data
		vec3 position(vec3);
		vec3 position(void) const;

		quat rotation(quat);
		quat rotation(void) const;

		int screen(uint32_t, int);
		int screen(uint32_t) const;

		uint32_t modifiers(uint32_t);
		uint32_t modifiers(void) const;

		canvas::button button(void) const;
		canvas::button button(canvas::button);

		//rotation
		static vec3 arcball(float, float);
		static quat arcball(const vec3&, const vec3&);

	protected:
		int m_screen[2];
		vec3 m_position;
		quat m_rotation;
		uint32_t m_modifiers;
		canvas::button m_button;
	};
}