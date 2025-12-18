//def
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

//std
#include <cmath>
#include <cfloat>
#include <filesystem>

//OpenGL
#ifdef _WIN32
#include <Windows.h>
#endif
#include <GL/gl.h>

//stbi
#include "stb_image_write.h"

//canvas
#include "Canvas/Canvas/inc/Math/vec4.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/UBO.hpp"

#include "Canvas/Canvas/inc/Cameras/Camera.hpp"

#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

#include "Canvas/Canvas/inc/Animations/Cameras/Rotation.hpp"

namespace canvas
{
	namespace cameras
	{
		//constructors
		Camera::Camera(Scene* scene) : m_scene{scene}, 
			m_up{0, 1, 0}, m_target{0, 0, 0}, m_position{0, 0, 1},
			m_fov{float(M_PI_4)}, m_planes{1.00e-02f, 1.00e+02f},
			m_width{700}, m_height{700}, m_output{"screen"}, m_type{cameras::type::orthographic}
		{
			return;
		}

		//destructor
		Camera::~Camera(void)
		{
			return;
		}

		//update
		void Camera::bound(void)
		{
			//bound
			m_fov = float(M_PI_4);
			m_bounding_box.compute(m_scene, true, true);
			if(m_type == type::perspective) bound_perspective();
			if(m_type == type::orthographic) bound_orthographic();
			//update
			update();
		}
		void Camera::update(void)
		{
			compute();
			m_scene->m_ubos[0]->transfer( 0 * sizeof(float), 16 * sizeof(float), m_view.data());
			m_scene->m_ubos[0]->transfer(16 * sizeof(float), 16 * sizeof(float), m_projection.data());
		}
		void Camera::compute(void)
		{
			compute_view();
			m_type == type::perspective ? compute_perspective() : compute_orthographic();
		}

		//directions
		vec3 Camera::up(void) const
		{
			return m_up;
		}
		vec3 Camera::front(void) const
		{
			return (m_target - m_position).unit();
		}
		vec3 Camera::right(void) const
		{
			return (m_target - m_position).unit().cross(m_up);
		}
		vec3 Camera::target(void) const
		{
			return m_target;
		}
		vec3 Camera::position(void) const
		{
			return m_position;
		}
		void Camera::direction(const quat& q)
		{
			//data
			const float d = (m_target - m_position).norm();
			//update
			m_up = q.rotate({0, 1, 0});
			m_position = m_target + d * q.rotate({0, 0, 1});
		}

		//bounding box
		BoundingBox& Camera::bounding_box(void)
		{
			return m_bounding_box;
		}

		//screen
		uint32_t Camera::width(void) const
		{
			return m_width;
		}
		uint32_t Camera::height(void) const
		{
			return m_height;
		}

		//screen
		void Camera::screen_print(void) const
		{
			//data
			char path[200];
			uint32_t index = 0;
			const uint32_t w = m_width;
			const uint32_t h = m_height;
			uint32_t* buffer = new uint32_t[4 * w * h];
			//read
			glReadBuffer(GL_FRONT);
			glPixelStorei(GL_PACK_ALIGNMENT, 4);
			glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			//file
			while(true)
			{
				sprintf(path, "%s_%d.png", m_output.c_str(), index++);
				if(!std::filesystem::exists(path)) break;
			}
			//save
			stbi_flip_vertically_on_write(true);
			stbi_write_png(path, w, h, 4, buffer, 4 * w);
		}
		void Camera::screen_record(void) const
		{
			return;
		}

		//convertion
		vec3 Camera::world_to_screen(vec3 v) const
		{
			return (m_projection * m_view * vec4(v, 1)).reduce();
		}

		//type
		cameras::type Camera::type(void) const
		{
			return m_type;
		}
		cameras::type Camera::type(cameras::type type)
		{
			return m_type = type;
		}

		//callbacks
		void Camera::callback_key(char key)
		{
			if(key == 'p')
			{
				screen_print();
			}
			else if(key == 'f')
			{
				bound(), m_scene->update_on_motion();
			}
			else if(key == 'c')
			{
				m_type = cameras::type(!uint32_t(m_type));
				bound(), m_scene->update_on_motion();
			}
			else if(key == 'x' || key == 'y' || key == 'z' || key == 'i')
			{
				callback_rotation(key), m_scene->update_on_motion();
			}
		}
		void Camera::callback_wheel(bool direction)
		{
			callback_zoom(direction);
		}
		void Camera::callback_motion(int32_t x1, int32_t x2)
		{
			if(m_click.m_button == button::middle)
			{
				if(m_click.m_modifiers & uint32_t(modifier::shift))
				{
					callback_translation(x1, x2);
				}
				else
				{
					callback_rotation(x1, x2);
				}
			}
		}
		void Camera::callback_reshape(int32_t width, int32_t height)
		{
			//data
			m_width = width;
			m_height = height;
			//update
			bound();
			update();
			glViewport(0, 0, width, height);
		}
		void Camera::callback_mouse(canvas::button button, bool pressed, int x1, int x2, uint32_t modifiers)
		{
			if(pressed)
			{
				m_click.m_up = m_up;
				m_click.m_screen[0] = x1;
				m_click.m_screen[1] = x2;
				m_click.m_button = button;
				m_click.m_target = m_target;
				m_click.m_position = m_position;
				m_click.m_modifiers = modifiers;
			}
			else
			{
				m_click.m_button = canvas::button::none;
			}
		}

		//bound
		void Camera::bound_perspective(void)
		{
			//sphere
			const vec3 x_min = m_bounding_box.min();
			const vec3 x_max = m_bounding_box.max();
			const vec3 center = (x_max + x_min) / 2;
			const vec3 uf = (m_target - m_position).unit();
			const float radius = (x_max - x_min).norm() / 2;
			//fov
			const float t2 = tanf(m_fov / 2);
			const float t1 = m_width * t2 / m_height;
			//distance
			const float d = (1 + 1 / fminf(t1, t2)) * radius;
			//planes
			m_planes[0] = d - radius;
			m_planes[1] = d + radius;
			//position
			m_target = center;
			m_position = center - d * uf;
		}
		void Camera::bound_orthographic(void)
		{
			//sphere
			const vec3 x_min = m_bounding_box.min();
			const vec3 x_max = m_bounding_box.max();
			const vec3 center = (x_max + x_min) / 2;
			const vec3 uf = (m_target - m_position).unit();
			const float radius = (x_max - x_min).norm() / 2;
			//fov
			const float t2 = tanf(m_fov / 2);
			const float t1 = m_width * t2 / m_height;
			//planes
			m_planes[0] = radius / fminf(t1, t2);
			m_planes[1] = m_planes[0] + 2 * radius;
			//position
			m_target = center;
			m_position = center - (m_planes[0] + radius) * uf;
		}

		//compute
		void Camera::compute_view(void)
		{
			//data
			const vec3 up = m_up;
			const vec3 uf = (m_target - m_position).unit();
			const vec3 ur = uf.cross(m_up);
			//view
			m_view[3 + 4 * 3] = 1;
			m_view[0 + 4 * 0] = +ur[0];
			m_view[0 + 4 * 1] = +ur[1];
			m_view[0 + 4 * 2] = +ur[2];
			m_view[1 + 4 * 0] = +up[0];
			m_view[1 + 4 * 1] = +up[1];
			m_view[1 + 4 * 2] = +up[2];
			m_view[2 + 4 * 0] = -uf[0];
			m_view[2 + 4 * 1] = -uf[1];
			m_view[2 + 4 * 2] = -uf[2];
			m_view[0 + 4 * 3] = -ur.inner(m_position);
			m_view[1 + 4 * 3] = -up.inner(m_position);
			m_view[2 + 4 * 3] = +uf.inner(m_position);
			m_view[3 + 4 * 0] = m_view[3 + 4 * 1] = m_view[3 + 4 * 2] = 0;
		}
		void Camera::compute_perspective(void)
		{
			//data
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float t2 = tanf(m_fov / 2);
			const float t1 = m_width * t2 / m_height;
			//projection
			m_projection.zeros();
			m_projection[3 + 4 * 2] = -1;
			m_projection[0 + 4 * 0] = 1 / t1;
			m_projection[1 + 4 * 1] = 1 / t2;
			m_projection[2 + 4 * 2] = -(z1 + z2) / (z2 - z1);
			m_projection[2 + 4 * 3] = -2 * z1 * z2 / (z2 - z1);
		}
		void Camera::compute_orthographic(void)
		{
			//data
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float t2 = tanf(m_fov / 2);
			const float t1 = m_width * t2 / m_height;
			//projection
			m_projection.zeros();
			m_projection[3 + 4 * 3] = 1;
			m_projection[0 + 4 * 0] = 1 / z1 / t1;
			m_projection[1 + 4 * 1] = 1 / z1 / t2;
			m_projection[2 + 4 * 2] = -2 / (z2 - z1);
			m_projection[2 + 4 * 3] = -(z1 + z2) / (z2 - z1);
		}

		//callbacks
		void Camera::callback_zoom(bool direction)
		{
			//data
			const float a = 1.05f;
			const float s = direction ? a : 1 / a;
			m_fov = 2 * atanf(s * tan(m_fov / 2));
			//update
			update();
		}
		void Camera::callback_rotation(char key)
		{
			if(key == 'x')
			{
				const quat q({0, 1, 0}, {0, 0, 1}, {1, 0, 0});
				m_scene->add_animation(new animations::cameras::Rotation(this, q));
			}
			if(key == 'y')
			{
				const quat q({0, 0, 1}, {1, 0, 0}, {0, 1, 0});
				m_scene->add_animation(new animations::cameras::Rotation(this, q));
			}
			if(key == 'z')
			{
				const quat q({1, 0, 0}, {0, 1, 0}, {0, 0, 1});
				m_scene->add_animation(new animations::cameras::Rotation(this, q));
			}
			if(key == 'i')
			{
				static uint32_t index = 0;
				const quat q = quat::view_iso(index).conjugate();
				m_scene->add_animation(new animations::cameras::Rotation(this, q));
				index = (index + 1) % 3;
			}
		}
		void Camera::callback_rotation(int32_t x1, int32_t x2)
		{
			//data
			const float w = float(m_width);
			const float h = float(m_height);
			const float s1 = float(x1 - m_click.m_screen[0]);
			const float s2 = float(x2 - m_click.m_screen[1]);
			//click
			const vec3 uf = (m_click.m_target - m_click.m_position).unit();
			const vec3 ur = uf.cross(m_click.m_up);
			//screen
			const vec2 us = vec2(s1, s2).unit();
			const float t = 2 * float(M_PI) * vec2(s1, s2).norm() / fminf(w, h);
			//rotation
			const float d = (m_click.m_target - m_click.m_position).norm();
			const vec3 ut = us[1] * ur + us[0] * m_click.m_up;
			//camera
			m_up = (-t * ut).quaternion().rotate(m_click.m_up);
			m_position = m_click.m_target - d * (-t * ut).quaternion().rotate(uf);
			//update
			update();
			m_scene->update_on_motion();
		}
		void Camera::callback_translation(int32_t x1, int32_t x2)
		{
			//data
			const float d = (m_target - m_position).norm();
			//data
			const float w = float(m_width);
			const float h = float(m_height);
			const float s1 = float(x1 - m_click.m_screen[0]);
			const float s2 = float(x2 - m_click.m_screen[1]);
			//click
			const vec3 uf = (m_target - m_position).unit();
			const vec3 ur = uf.cross(m_click.m_up);
			//screen
			const vec2 us = vec2(s1, s2).unit();
			const float t = d * vec2(s1, s2).norm() / fminf(w, h);
			//camera
			m_target = m_click.m_target + t * (us[1] * m_click.m_up - us[0] * ur);
			m_position = m_click.m_position + t * (us[1] * m_click.m_up - us[0] * ur);
			//update
			update();
			m_scene->update_on_motion();
		}
	}
}