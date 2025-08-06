#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/mat4.hpp"

#include "Canvas/Canvas/inc/Cameras/Click.hpp"

namespace canvas
{
	class Scene;
	namespace cameras
	{
		enum class type : uint32_t
		{
			perspective,
			orthographic
		};
	}
}

namespace canvas
{
	namespace cameras
	{
		class Camera
		{
		public:
			//constructors
			Camera(Scene*);

			//destructor
			~Camera(void);

			//update
			void bound(void);
			void update(void);
			void compute(void);

			//directions
			vec3 up(void) const;
			vec3 front(void) const;
			vec3 right(void) const;
			vec3 target(void) const;
			vec3 position(void) const;
			void direction(const quat&);

			//screen
			uint32_t width(void) const;
			uint32_t height(void) const;

			//serialization
			void screen_print(void) const;
			void screen_record(void) const;

			//world
			vec3 world_to_screen(vec3) const;

			//type
			cameras::type type(void) const;
			cameras::type type(cameras::type);

			//callbacks
			void callback_key(char);
			void callback_wheel(bool);
			void callback_motion(int32_t, int32_t);
			void callback_reshape(int32_t, int32_t);
			void callback_mouse(button, bool, int32_t, int32_t, uint32_t);

		protected:
			//compute
			void compute_view(void);
			void compute_perspective(void);
			void compute_orthographic(void);

			//callbacks
			void callback_zoom(bool);
			void callback_rotation(char);
			void callback_rotation(int32_t, int32_t);
			void callback_translation(int32_t, int32_t);

			//bound
			void bound_test(void) const;
			bool bound_test(const vec3&) const;
			void bound_text_3D(vec3&, vec3&, bool&) const;
			void bound_model_3D(vec3&, vec3&, bool&) const;
			void bound_image_3D(vec3&, vec3&, bool&) const;
			void bound_checkup_3D(vec3&, vec3&, bool&) const;
			void bound_perspective(const vec3&, const vec3&);
			void bound_orthographic(const vec3&, const vec3&);

			//data
			Scene* m_scene;

			vec3 m_up;
			vec3 m_target;
			vec3 m_position;

			float m_fov;
			float m_planes[2];

			mat4 m_view;
			mat4 m_projection;

			Click m_click;
			uint32_t m_width;
			uint32_t m_height;
			std::string m_output;
			cameras::type m_type;

			//friends
			friend class canvas::Scene;
		};
	}
}