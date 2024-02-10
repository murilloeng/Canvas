//def
#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

//os
#ifdef _WIN32
#include <Windows.h>
#endif

//std
#include <cmath>
#include <cfloat>
#include <filesystem>

//ext
#include "external/cpp/inc/GL/glew.h"
#include "stb_image_write.h"

//canvas
#include "Canvas/inc/GPU/Program.hpp"
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Scene/Camera.hpp"
#include "Canvas/inc/Vertices/Text.hpp"
#include "Canvas/inc/Vertices/Model.hpp"
#include "Canvas/inc/Vertices/Image.hpp"

namespace canvas
{
	namespace camera
	{

		//constructors
		Camera::Camera(void) : m_type(camera::type::orthogonal), m_fov(M_PI / 3), m_plane_far(2.0f), m_plane_near(1.0f), m_output("screen")
		{
			return;
		}

		//destructor
		Camera::~Camera(void)
		{
			return;
		}

		//data
		vec3 Camera::position(void) const
		{
			return m_position;
		}
		vec3 Camera::position(const vec3& position)
		{
			return m_position = position;
		}

		quat Camera::rotation(char mode)
		{
			if(mode == 'x')
			{
				return rotation(quat::view_x1().conjugate());
			}
			else if(mode == 'y')
			{
				return rotation(quat::view_x2().conjugate());
			}
			else if(mode == 'z')
			{
				return rotation(quat::view_x3().conjugate());
			}
			else if(mode == 'i')
			{
				static unsigned index = 1;
				return rotation(quat::view_iso(index = (index + 1) % 3).conjugate());
			}
			else
			{
				return quat();
			}
		}
		quat Camera::rotation(void) const
		{
			return m_rotation;
		}
		quat Camera::rotation(const quat& rotation)
		{
			return m_rotation = rotation;
		}
		quat Camera::rotation(const vec3& rotation)
		{
			return m_rotation = rotation.quaternion();
		}

		unsigned Camera::width(void) const
		{
			return m_width;
		}
		unsigned Camera::height(void) const
		{
			return m_height;
		}

		float Camera::fov(float fov)
		{
			return m_fov = fov;
		}
		float Camera::fov(void) const
		{
			return m_fov;
		}
		float Camera::plane_far(void) const
		{
			return m_plane_far;
		}
		float Camera::plane_near(void) const
		{
			return m_plane_near;
		}
		float Camera::plane_far(float plane_far)
		{
			return m_plane_far = plane_far;
		}
		float Camera::plane_near(float plane_near)
		{
			return m_plane_near = plane_near;
		}

		camera::type Camera::type(void) const
		{
			return m_type;
		}
		camera::type Camera::type(camera::type type)
		{
			return m_type = type;
		}

		//screen
		void Camera::screen_print(void) const
		{
			//data
			char path[200];
			unsigned index = 0;
			const unsigned w = m_width;
			const unsigned h = m_height;
			unsigned* buffer = new unsigned[4 * w * h];
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

		//update
		void Camera::apply(void)
		{
			apply_view();
			m_type == camera::type::orthogonal ? apply_orthogonal() : apply_perspective();
		}
		void Camera::bound(void)
		{
			m_type == camera::type::orthogonal ? bound_orthogonal() : bound_perspective();
		}
		void Camera::update(void)
		{
			for(unsigned i = 0; i < 4; i++)
			{
				m_programs[i].use();
				glUniformMatrix4fv(m_programs[i].uniform("view"), 1, false, m_view.data());
				glUniformMatrix4fv(m_programs[i].uniform("projection"), 1, false, m_projection.data());
			}
			m_programs[1].use();
			glUniform3f(m_programs[1].uniform("camera_position"), m_position[0], m_position[1], -m_position[2]);
		}

		//callbacks
		void Camera::callback_keyboard(char key)
		{
			// if(key == 'p') screen_print();
			// else if(key == 'f') bound(), update_shaders();
			// else if(key == '-') callback_wheel(-1, m_screen[0] / 2, m_screen[1] / 2);
			// else if(key == '+') callback_wheel(+1, m_screen[0] / 2, m_screen[1] / 2);
			// else if(key == 'x' || key == 'y' || key == 'z' || key == 'i') rotation(key), bound(), update_shaders();
		}
		void Camera::callback_motion(int x1, int x2)
		{
			// //data
			// const float s = m_scale;
			// const float z1 = m_planes[0];
			// const float z2 = m_planes[1];
			// const int a1 = m_click.screen(0);
			// const int a2 = m_click.screen(1);
			// const vec3 xc = m_click.position();
			// const quat qc = m_click.rotation();
			// const float w = (float) m_screen[0];
			// const float h = (float) m_screen[1];
			// //arcball
			// const float m = fminf(w, h);
			// const vec3 v1 = Click::arcball((2 * a1 - w) / m, (h - 2 * a2) / m);
			// const vec3 v2 = Click::arcball((2 * x1 - w) / m, (h - 2 * x2) / m);
			// //shift
			// if(m_click.button() == button::middle)
			// {
			// 	const float b1 = 2 * s * (x1 - a1) / m;
			// 	const float b2 = 2 * s * (a2 - x2) / m;
			// 	m_position = m_click.position() - m_rotation.rotate({b1, b2, 0});
			// }
			// //rotation
			// if(m_click.button() == button::left)
			// {
			// 	m_rotation = qc * Click::arcball(v1, v2);
			// 	m_position = xc + (z1 + z2) / 2 * (qc.rotate({0, 0, 1}) - m_rotation.rotate({0, 0, 1}));
			// }
			// if(m_click.button() != button::none) update_shaders();
		}
		void Camera::callback_reshape(int width, int height)
		{
			//data
			m_width = width;
			m_height = height;
			//update
			bound();
			apply();
			update();
			glViewport(0, 0, width, height);
		}
		void Camera::callback_wheel(int direction, int x1, int x2)
		{
			// //data
			// const float ds = 1.05f;
			// const float s = m_scale;
			// const quat& qc = m_rotation;
			// const float w = (float) m_screen[0];
			// const float h = (float) m_screen[1];
			// const float s1 = 2 * float(x1) / w - 1;
			// const float s2 = 1 - 2 * float(x2) / h;
			// //update
			// const float m = fminf(w, h);
			// m_scale = direction > 0 ? s / ds : s * ds;
			// m_position -= (m_scale - s) * qc.rotate({w / m * s1, h / m * s2, 0});
			// //shaders
			// update_shaders();
		}
		void Camera::callback_special(canvas::key key, unsigned modifiers, int x1, int x2)
		{
			// //data
			// const float ds = 0.05f;
			// const float s = m_scale;
			// const quat qn = m_rotation;
			// const quat& qc = m_rotation;
			// const float z1 = m_planes[0];
			// const float z2 = m_planes[1];
			// const float dt = float(M_PI) / 12;
			// const float w = (float) m_screen[0];
			// const float h = (float) m_screen[1];
			// const vec3 shift[] = {{-ds, 0, 0}, {+ds, 0, 0}, {0, -ds, 0}, {0, +ds, 0}};
			// const vec3 rotation[] = {{0, -dt, 0}, {0, +dt, 0}, {+dt, 0, 0}, {-dt, 0, 0}};
			// const canvas::key keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
			// //affine
			// for(unsigned i = 0; i < 4; i++)
			// {
			// 	if(key == keys[i])
			// 	{
			// 		if(modifiers & 1 << unsigned(modifier::alt))
			// 		{
			// 			const float m = fminf(w, h);
			// 			m_position -= qc.rotate(s * mat4::scaling({w / m, h / m, 1}) * shift[i]);
			// 		}
			// 		else if(modifiers & 1 << unsigned(modifier::ctrl))
			// 		{
			// 			m_rotation = rotation[i].quaternion().conjugate() * m_rotation;
			// 			m_position += (z1 + z2) / 2 * (qn.rotate({0, 0, 1}) - qc.rotate({0, 0, 1}));
			// 		}
			// 		else if(modifiers & 1 << unsigned(modifier::shift))
			// 		{
			// 			m_rotation = m_rotation * rotation[i].quaternion().conjugate();
			// 			m_position += (z1 + z2) / 2 * (qn.rotate({0, 0, 1}) - qc.rotate({0, 0, 1}));
			// 		}
			// 		update_shaders();
			// 	}
			// }
		}
		void Camera::callback_mouse(canvas::button button, bool pressed, int x1, int x2)
		{
			if(pressed)
			{
				m_click.screen(0, x1);
				m_click.screen(1, x2);
				m_click.button(button);
				m_click.position(m_position);
				m_click.rotation(m_rotation);
			}
			else
			{
				m_click.button(canvas::button::none);
			}
		}

		//apply
		void Camera::apply_view(void)
		{
			m_view = m_rotation.conjugate().rotation() * (-m_position).shift();
		}
		void Camera::apply_orthogonal(void)
		{
			//data
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			const float z2 = m_plane_far;
			const float z1 = m_plane_near;
			//projection
			m_projection.clear();
			m_projection(2, 2) = -2 / (z2 - z1);
			m_projection(0, 0) = +2 * m / w / (z2 - z1);
			m_projection(1, 1) = +2 * m / h / (z2 - z1);
			m_projection(2, 3) = -(z1 + z2) / (z2 - z1);
		}
		void Camera::apply_perspective(void)
		{
			//data
			const float a = m_fov;
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			const float z2 = m_plane_far;
			const float z1 = m_plane_near;
			//projection
			m_projection.clear();
			m_projection(3, 3) = +0.0f;
			m_projection(3, 2) = -1.0f;
			m_projection(1, 1) = m / h / tanf(a / 2);
			m_projection(0, 0) = m / w / tanf(a / 2);
			m_projection(2, 2) = -(z1 + z2) / (z2 - z1);
			m_projection(2, 3) = -2 * z1 * z2 / (z2 - z1);
		}

		//bound
		void Camera::bound_orthogonal(void)
		{
			//data
			vec3 xw;
			const float q = FLT_MAX;
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			const quat& qc = m_rotation;
			const vec3 xr = bound_center();
			float v1 = 0, v2 = 0, z1 = +q, z2 = -q;
			//bound
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < m_scene->m_vbo_size[i]; j++)
				{
					//position
					if(i == 2) xw = qc.conjugate(((vertices::Text*) m_scene->m_vbo_data[i] + j)->m_position);
					if(i == 0) xw = qc.conjugate(((vertices::Model*) m_scene->m_vbo_data[i] + j)->m_position);
					if(i == 1) xw = qc.conjugate(((vertices::Image*) m_scene->m_vbo_data[i] + j)->m_position);
					//bound
					z1 = fminf(z1, xw[2] - xr[2]);
					z2 = fmaxf(z2, xw[2] - xr[2]);
					v1 = fmaxf(v1, fabsf(xw[0] - xr[0]));
					v2 = fmaxf(v2, fabsf(xw[1] - xr[1]));
				}
			}
			//planes
			m_plane_far = 1.0f;
			m_plane_near = 1.0f;
			m_plane_far = fmaxf(m_plane_far, m_plane_near + z2 - z1);
			m_plane_far = fmaxf(m_plane_far, m_plane_near + 2 * m / w * v1);
			m_plane_far = fmaxf(m_plane_far, m_plane_near + 2 * m / h * v2);
			//position
			m_position = qc.rotate(xr + vec3(0, 0, (m_plane_far + m_plane_near + z1 + z2) / 2));
		}
		void Camera::bound_perspective(void)
		{
			//data
			vec3 xw;
			const float a = m_fov;
			const float q = FLT_MAX;
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			const quat& qc = m_rotation;
			const vec3 xr = bound_center();
			//offset
			float e = 0, z1 = +q, z2 = -q;
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < m_scene->m_vbo_size[i]; j++)
				{
					//position
					if(i == 2) xw = qc.conjugate(((vertices::Text*) m_scene->m_vbo_data[i] + j)->m_position);
					if(i == 0) xw = qc.conjugate(((vertices::Model*) m_scene->m_vbo_data[i] + j)->m_position);
					if(i == 1) xw = qc.conjugate(((vertices::Image*) m_scene->m_vbo_data[i] + j)->m_position);
					//bound
					z1 = fminf(z1, xw[2] - xr[2]);
					z2 = fmaxf(z2, xw[2] - xr[2]);
					e = fmaxf(e, xw[2] - xr[2] + m / w * fabsf(xw[0] - xr[0]) / tanf(a / 2));
					e = fmaxf(e, xw[2] - xr[2] + m / h * fabsf(xw[1] - xr[1]) / tanf(a / 2));
				}
			}
			//planes
			m_plane_far = e - z1;
			m_plane_near = e - z2;
			//position
			m_position = qc.rotate(xr + vec3(0, 0, e));
		}
		vec3 Camera::bound_center(void) const
		{
			//data
			const float a = FLT_MAX;
			const quat& qc = m_rotation;
			//check
			if(m_scene->m_objects.empty()) return vec3(0, 0, 0);
			//bound
			vec3 xw;
			vec3 x_min = {+a, +a, +a};
			vec3 x_max = {-a, -a, -a};
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < m_scene->m_vbo_size[i]; j++)
				{
					//position
					if(i == 2) xw = qc.conjugate(((vertices::Text*) m_scene->m_vbo_data[i] + j)->m_position);
					if(i == 0) xw = qc.conjugate(((vertices::Model*) m_scene->m_vbo_data[i] + j)->m_position);
					if(i == 1) xw = qc.conjugate(((vertices::Image*) m_scene->m_vbo_data[i] + j)->m_position);
					//bouding box
					x_min[0] = fminf(x_min[0], xw[0]);
					x_max[0] = fmaxf(x_max[0], xw[0]);
					x_min[1] = fminf(x_min[1], xw[1]);
					x_max[1] = fmaxf(x_max[1], xw[1]);
					x_min[2] = fminf(x_min[2], xw[2]);
					x_max[2] = fmaxf(x_max[2], xw[2]);
				}
			}
			//return
			return (x_min + x_max) / 2;
		}
	}
}