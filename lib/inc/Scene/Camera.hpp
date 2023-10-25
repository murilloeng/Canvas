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
	class Program;
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
		vec3 position(void) const;
		vec3 position(const vec3&);

		quat rotation(char);
		quat rotation(void) const;
		quat rotation(const quat&);

		bool orthogonal(bool);
		bool orthogonal(void) const;

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

	protected:
		//data
		Click m_click;
		vec3 m_position;
		quat m_rotation;
		bool m_orthogonal;
		Program* m_programs;
		std::string m_output;
		unsigned m_screen[2];

		//friends
		friend class Scene;
	};
}