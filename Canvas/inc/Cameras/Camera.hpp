#pragma once

//std
#include <string>
#include <vector>
#include <cstdint>

//canvas
#include "Canvas/Canvas/inc/Math/vec3.hpp"
#include "Canvas/Canvas/inc/Math/quat.hpp"

#include "Canvas/Canvas/inc/Cameras/Click.hpp"

#include "Canvas/Canvas/inc/shaders/Shader.hpp"

namespace canvas
{
	class Scene;
}

namespace canvas
{
	namespace camera
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

			uint32_t width(uint32_t);
			uint32_t width(void) const;

			uint32_t height(uint32_t);
			uint32_t height(void) const;

			float plane(uint32_t) const;
			float plane(uint32_t, float);

			camera::type type(void) const;
			camera::type type(camera::type);

			//screen
			void screen_print(void) const;
			void screen_record(void) const;

			//shaders
			void bound(void);
			void update(void);

			//callbacks
			void callback_keyboard(char);
			void callback_motion(int, int);
			void callback_reshape(int, int);
			void callback_wheel(int, int, int);
			void callback_mouse(button, bool, int, int);
			void callback_special(key, uint32_t, int, int);

		protected:
			//compute
			void compute_view(float*) const;
			void compute_perspective(float*) const;
			void compute_orthographic(float*) const;

			//bound
			void bound_box(void);
			void bound_check(void);
			void bound_limits(void);
			void bound_search_1(void);
			void bound_search_2(void);
			void bound_bisection_1(void);
			void bound_bisection_2(void);
			void bound_perspective(void);
			void bound_orthographic(void);
			float bound_bisection_1(float);
			float bound_bisection_2(float);

			//data
			Click m_click;
			Scene* m_scene;
			camera::type m_type;

			vec3 m_position;
			quat m_rotation;

			uint32_t m_width;
			uint32_t m_height;
			std::string m_output;

			vec3 m_x_min;
			vec3 m_x_max;

			float m_fov;
			float m_scale;
			float m_planes[2];
			std::vector<vec3> m_bounds;
			const std::vector<shaders::Shader*>& m_shaders;

			//friends
			friend class canvas::Scene;
		};
	}
}