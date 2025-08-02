//def
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

//std
#include <cmath>
#include <cfloat>
#include <filesystem>

//ext
#include "stb_image_write.h"
#include "external/cpp/inc/GL/glew.h"

//canvas
#include "Canvas/Canvas/inc/Math/vec4.hpp"

#include "Canvas/Canvas/inc/Scene/Scene.hpp"

#include "Canvas/Canvas/inc/Buffers/VBO.hpp"
#include "Canvas/Canvas/inc/Buffers/Buffer.hpp"

#include "Canvas/Canvas/inc/Cameras/Camera.hpp"

#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

#include "Canvas/Canvas/inc/Shaders/Shader.hpp"

namespace canvas
{
	namespace cameras
	{

		//constructors
		Camera::Camera(Scene* scene) : m_scene(scene), 
			m_up{0, 1, 0}, m_target{0, 0, 0}, m_position{0, 0, 1},
			m_fov{float(M_PI_4)}, m_planes_far{1.00e+02f}, m_planes_near{1.00e-02f},
			m_width(700), m_height(700), m_output("screen"), m_type(cameras::type::orthographic)
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
			//data
			vec3 x_min, x_max;
			bool status = false;
			//bound
			bound_text_3D(x_min, x_max, status);
			bound_model_3D(x_min, x_max, status);
			bound_image_3D(x_min, x_max, status);
			bound_checkup_3D(x_min, x_max, status);
			//sphere
			const vec3 center = (x_max + x_min) / 2;
			const vec3 uf = (m_target - m_position).unit();
			const float radius = (x_max - x_min).norm() / 2;
			//fov
			const float fov_2 = m_fov;
			const float fov_1 = 2 * atanf(m_width * tanf(fov_2 / 2) / m_height);
			//distance
			const float d_2 = radius / tanf(fov_2 / 2);
			const float d_1 = radius / tanf(fov_1 / 2);
			//position
			m_target = center;
			m_position = center - fmaxf(d_1, d_2) * uf;
			//planes
			m_planes_far = fmaxf(d_1, d_2) + radius;
			m_planes_near = fmaxf(d_1, d_2) - radius;
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
			else if(key == 'x' || key == 'y' || key == 'z' || key == 'i')
			{
				callback_rotation(key), bound(), m_scene->update_on_motion();
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
			const float z2 = m_planes_far;
			const float z1 = m_planes_near;
			const float tf = tanf(m_fov / 2);
			const float ar = (float) m_width / m_height;
			//projection
			m_projection.zeros();
			m_projection[3 + 4 * 2] = -1;
			m_projection[1 + 4 * 1] = 1 / tf;
			m_projection[0 + 4 * 0] = 1 / tf / ar;
			m_projection[2 + 4 * 2] = -(z2 + z1) / (z2 - z1);
			m_projection[2 + 4 * 3] = -2 * z1 * z2 / (z2 - z1);
		}
		void Camera::compute_orthographic(void)
		{
			//data
			const float z2 = m_planes_far;
			const float z1 = m_planes_near;
			const float tf = tanf(m_fov / 2);
			const float ar = (float) m_width / m_height;
			//projection
			m_projection.zeros();
			m_projection[3 + 4 * 2] = -1;
			m_projection[1 + 4 * 1] = 1 / tf;
			m_projection[0 + 4 * 0] = 1 / tf / ar;
			m_projection[2 + 4 * 2] = -(z2 + z1) / (z2 - z1);
			m_projection[2 + 4 * 3] = -2 * z1 * z2 / (z2 - z1);
		}

		//callbacks
		void Camera::callback_zoom(bool direction)
		{
			//data
			const float a = 1.05f;
			const vec3 uf = (m_target - m_position).unit();
			const float d = (m_target - m_position).norm();
			//position
			m_position = m_target - (direction ? a * d : d / a) * uf;
			//update
			update();
		}
		void Camera::callback_rotation(char key)
		{
			if(key == 'x')
			{
				m_up = {0, 0, 1};
				m_position = m_target + vec3(1, 0, 0);
			}
			if(key == 'y')
			{
				m_up = {1, 0, 0};
				m_position = m_target + vec3(0, 1, 0);
			}
			if(key == 'z')
			{
				m_up = {0, 1, 0};
				m_position = m_target + vec3(0, 0, 1);
			}
			if(key == 'i')
			{
				//data
				static uint32_t index = 0;
				const quat q = quat::view_iso(index).conjugate();
				//update
				index = (index + 1) % 3;
				m_up = q.rotate({0, 1, 0});
				m_position = m_target + q.rotate({0, 0, 1});
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

		//bound
		void Camera::bound_text_3D(vec3& x_min, vec3& x_max, bool& status) const
		{
			//data
			vertices::Text3D* data = (vertices::Text3D*) m_scene->m_vbos[2]->m_data;
			//setup
			if(!status && m_scene->m_vbos[2]->m_vertex_count)
			{
				status = true;
				x_min = x_max = data[0].m_position;
			}
			//bound
			for(uint32_t i = 0; i < m_scene->m_vbos[2]->m_vertex_count; i++)
			{
				for(uint32_t j = 0; j < 3; j++)
				{
					x_min[j] = fminf(x_min[j], data[i].m_position[j]);
					x_max[j] = fmaxf(x_max[j], data[i].m_position[j]);
				}
			}
		}
		void Camera::bound_model_3D(vec3& x_min, vec3& x_max, bool& status) const
		{
			//data
			vertices::Model3D* data = (vertices::Model3D*) m_scene->m_vbos[0]->m_data;
			//setup
			if(!status && m_scene->m_vbos[0]->m_vertex_count)
			{
				status = true;
				x_min = x_max = data[0].m_position;
			}
			//bound
			for(uint32_t i = 0; i < m_scene->m_vbos[0]->m_vertex_count; i++)
			{
				for(uint32_t j = 0; j < 3; j++)
				{
					x_min[j] = fminf(x_min[j], data[i].m_position[j]);
					x_max[j] = fmaxf(x_max[j], data[i].m_position[j]);
				}
			}
		}
		void Camera::bound_image_3D(vec3& x_min, vec3& x_max, bool& status) const
		{
			//data
			vertices::Image3D* data = (vertices::Image3D*) m_scene->m_vbos[1]->m_data;
			//setup
			if(!status && m_scene->m_vbos[1]->m_vertex_count)
			{
				status = true;
				x_min = x_max = data[0].m_position;
			}
			//bound
			for(uint32_t i = 0; i < m_scene->m_vbos[1]->m_vertex_count; i++)
			{
				for(uint32_t j = 0; j < 3; j++)
				{
					x_min[j] = fminf(x_min[j], data[i].m_position[j]);
					x_max[j] = fmaxf(x_max[j], data[i].m_position[j]);
				}
			}
		}
		void Camera::bound_checkup_3D(vec3& x_min, vec3& x_max, bool& status) const
		{
			if(!status)
			{
				x_min = {-1, -1, -1};
				x_max = {+1, +1, +1};
			}
			if((x_max - x_min).norm() < 1e-5)
			{
				x_min -= vec3(1, 1, 1);
				x_max += vec3(1, 1, 1);
			}
		}
	}
}