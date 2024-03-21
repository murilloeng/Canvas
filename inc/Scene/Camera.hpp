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
			float fov(float);
			float fov(void) const;

			vec3 x_min(vec3);
			vec3 x_min(void) const;

			vec3 x_max(vec3);
			vec3 x_max(void) const;

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
			void bound_center(void);
			void bound_orthogonal(void);
			void bound_perspective(void);

			//data
			Click m_click;
			Scene* m_scene;
			Program* m_programs;
			camera::type m_type;

			vec3 m_position;
			quat m_rotation;

			unsigned m_width;
			unsigned m_height;

			float m_fov;
			float m_scale;
			float m_planes[2];

			mat4 m_view;
			vec3 m_x_min;
			vec3 m_x_max;
			mat4 m_projection;

			std::string m_output;

			//friends
			friend class canvas::Scene;
		};
	}
}