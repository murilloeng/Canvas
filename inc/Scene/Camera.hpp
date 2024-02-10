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
	namespace camera
	{
		enum class type : unsigned
		{
			orthogonal,
			perspective
		};
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
			quat rotation(const vec3&);
			quat rotation(const quat&);

			unsigned width(void) const;
			unsigned height(void) const;

			float fov(float);
			float fov(void) const;
			float plane_far(float);
			float plane_near(float);
			float plane_far(void) const;
			float plane_near(void) const;

			camera::type type(void) const;
			camera::type type(camera::type);

			//screen
			void screen_print(void) const;
			void screen_record(void) const;

			//shaders
			void apply(void);
			void bound(void);
			void update(void);

			//callbacks
			void callback_keyboard(char);
			void callback_motion(int, int);
			void callback_reshape(int, int);
			void callback_wheel(int, int, int);
			void callback_mouse(button, bool, int, int);
			void callback_special(key, unsigned, int, int);

		protected:
			//apply
			void apply_view(void);
			void apply_orthogonal(void);
			void apply_perspective(void);

			//bound
			void bound_orthogonal(void);
			void bound_perspective(void);
			vec3 bound_center(void) const;

			//data
			Click m_click;
			Scene* m_scene;
			Program* m_programs;
			camera::type m_type;

			vec3 m_position;
			quat m_rotation;

			float m_fov;
			unsigned m_width;
			unsigned m_height;

			float m_plane_far;
			float m_plane_near;

			mat4 m_view;
			mat4 m_projection;

			std::string m_output;

			//friends
			friend class canvas::Scene;
		};
	}
}