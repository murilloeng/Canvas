#pragma once

//std
#include <string>
#include <vector>

//canvas
#include "Canvas/inc/Math/vec3.hpp"
#include "Canvas/inc/Math/quat.hpp"
#include "Canvas/inc/Math/mat4.hpp"
#include "Canvas/inc/Scene/Click.hpp"

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
		float scale(float);
		float scale(void) const;

		vec3 position(void) const;
		vec3 position(const vec3&);

		quat rotation(char);
		quat rotation(void) const;
		quat rotation(const vec3&);
		quat rotation(const quat&);

		unsigned width(void) const;
		unsigned height(void) const;

		float plane(unsigned) const;
		float plane(unsigned, float);

		//screen
		void screen_print(void) const;
		void screen_record(void) const;

		//shaders
		void bound(void);
		void update_shaders(void);

		//callbacks
		void callback_keyboard(char);
		void callback_motion(int, int);
		void callback_reshape(int, int);
		void callback_wheel(int, int, int);
		void callback_mouse(button, bool, int, int);
		void callback_special(key, unsigned, int, int);

	protected:
		//update
		void bound_box(void);
		void update_view(void);
		void update_projection(void);

		//data
		float m_scale;
		Click m_click;
		Scene* m_scene;
		vec3 m_box_min;
		vec3 m_box_max;
		vec3 m_position;
		quat m_rotation;
		float m_planes[2];

		Program* m_programs;
		std::string m_output;
		unsigned m_screen[2];

		mat4 m_view_matrix;
		mat4 m_projection_matrix;

		//friends
		friend class Scene;
	};
}