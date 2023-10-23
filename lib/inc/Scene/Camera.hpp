#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
#include "inc/Scene/Click.hpp"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	class Camera
	{
	public:
		//constructors
		Camera(void);

		//destructor
		~Camera(void);

		//data
		float zoom(float);
		float zoom(void) const;

		vec3 shift(void) const;
		vec3 shift(const vec3&);

		vec3 box_min(void) const;
		void box_min(const vec3&);

		vec3 box_max(void) const;
		void box_max(const vec3&);

		quat rotation(char);
		quat rotation(void) const;
		quat rotation(const quat&);

		unsigned width(void) const;
		unsigned height(void) const;

		//screen
		void screen_print(void) const;
		void screen_record(void) const;

		//callbacks
		void callback_motion(int, int);
		void callback_reshape(int, int);
		void callback_wheel(int, int, int);
		void callback_keyboard(char, int, int);
		void callback_mouse(button, bool, int, int);
		void callback_special(key, unsigned, int, int);

	private:
		//data
		float m_zoom;
		vec3 m_shift;
		Click m_click;
		vec3 m_box_min;
		vec3 m_box_max;
		quat m_rotation;
		std::string m_output;
		unsigned m_screen[2];
		unsigned* m_program_id;

		//friends
		friend class Scene;
	};
}