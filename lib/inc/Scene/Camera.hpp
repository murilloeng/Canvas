#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "inc/Math/vec3.hpp"
#include "inc/Math/quat.hpp"
#include "inc/Math/mat4.hpp"
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
		bool mode(bool);
		bool mode(void) const;

		vec3 position(void) const;
		vec3 position(const vec3&);

		quat rotation(char);
		quat rotation(void) const;
		quat rotation(const quat&);

		unsigned width(void) const;
		unsigned height(void) const;

		float plane_far(float);
		float plane_far(void) const;

		float plane_near(float);
		float plane_near(void) const;

		//screen
		void screen_print(void) const;
		void screen_record(void) const;

		//shaders
		void projection(void);
		void update_shaders(void) const;

		//callbacks
		void callback_motion(int, int);
		void callback_reshape(int, int);
		void callback_wheel(int, int, int);
		void callback_keyboard(char, int, int);
		void callback_mouse(button, bool, int, int);
		void callback_special(key, unsigned, int, int);

	protected:
		//projection
		void projection_orthogonal(void);
		void projection_perspective(void);

		//data
		bool m_mode;
		Click m_click;
		Scene* m_scene;
		vec3 m_position;
		quat m_rotation;
		mat4 m_projection;
		float m_plane_far;
		float m_plane_near;
		Program* m_programs;
		std::string m_output;
		unsigned m_screen[2];

		//friends
		friend class Scene;
	};
}