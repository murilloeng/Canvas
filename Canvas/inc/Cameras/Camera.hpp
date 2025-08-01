#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/quat.hpp"

#include "Canvas/Canvas/inc/Cameras/Click.hpp"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace cameras
	{
		enum class type : uint32_t
		{
			perspective,
			orthographic
		};
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

			//rotation
			quat rotation(void) const;

			//screen
			uint32_t width(void) const;
			uint32_t height(void) const;

			//screen
			void screen_print(void) const;
			void screen_record(void) const;

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
			//bound
			void bound_text_3D(vec3&, vec3&, bool&) const;
			void bound_model_3D(vec3&, vec3&, bool&) const;
			void bound_image_3D(vec3&, vec3&, bool&) const;
			void bound_checkup_3D(vec3&, vec3&, bool&) const;

			//compute
			void compute_view(float*) const;
			void compute_perspective(float*) const;
			void compute_orthographic(float*) const;

			//callbacks
			void callback_zoom(bool);
			void callback_rotation(char);
			void callback_rotation(int32_t, int32_t);
			void callback_translation(int32_t, int32_t);

			//data
			Click m_click;
			Scene* m_scene;
			
			vec3 m_up;
			vec3 m_target;
			vec3 m_position;

			float m_fov;
			float m_planes_far;
			float m_planes_near;
			
			uint32_t m_width;
			uint32_t m_height;
			std::string m_output;
			cameras::type m_type;

			//friends
			friend class canvas::Scene;
		};
	}
}