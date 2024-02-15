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
		Camera::Camera(void) : m_type(camera::type::orthogonal), m_scale(1.0f), m_plane_far(2.0f), m_plane_near(1.0f), m_output("screen")
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

		float Camera::scale(void) const
		{
			return m_scale;
		}
		float Camera::plane_far(void) const
		{
			return m_plane_far;
		}
		float Camera::plane_near(void) const
		{
			return m_plane_near;
		}

		float Camera::scale(float scale)
		{
			return m_scale = scale;
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
			if(key == 'p') screen_print();
			else if(key == 'f') bound(), apply(), update();
			else if(key == '-') callback_wheel(-1, m_width / 2, m_height / 2);
			else if(key == '+') callback_wheel(+1, m_width / 2, m_height / 2);
			else if(key == 'c') m_type = camera::type(!unsigned(m_type)), bound(),apply(), update();
			else if(key == 'x' || key == 'y' || key == 'z' || key == 'i') rotation(key), bound(), apply(), update();
		}
		void Camera::callback_motion(int x1, int x2)
		{
			//data
			const float s = m_scale;
			const float w = m_width;
			const float h = m_height;
			const float z2 = m_plane_far;
			const float z1 = m_plane_near;
			const int a1 = m_click.screen(0);
			const int a2 = m_click.screen(1);
			const vec3 xc = m_click.position();
			const quat qc = m_click.rotation();
			//arcball
			const float m = fminf(w, h);
			const vec3 v1 = Click::arcball((2 * a1 - w) / m, (h - 2 * a2) / m);
			const vec3 v2 = Click::arcball((2 * x1 - w) / m, (h - 2 * x2) / m);
			//shift
			if(m_click.button() == button::middle)
			{
				if(m_type == type::orthogonal)
				{
					const float b1 = 2 * s / m * (a1 - x1);
					const float b2 = 2 * s / m * (x2 - a2);
					m_position = m_click.position() + m_rotation.rotate({b1, b2, 0});
				}
				if(m_type == type::perspective)
				{
					const float v3 = -2 * z1 * z2 / (z1 + z2);
					const float b1 = -2 * s * v3 / m * (a1 - x1);
					const float b2 = -2 * s * v3 / m * (x2 - a2);
					m_position = m_click.position() + m_rotation.rotate({b1, b2, 0});
				}
			}
			//rotation
			if(m_click.button() == button::left)
			{
				m_rotation = qc * Click::arcball(v1, v2).conjugate();
				m_position = xc + (z1 + z2) / 2 * (qc.rotate({0, 0, 1}) - m_rotation.rotate({0, 0, 1}));
			}
			if(m_click.button() != button::none) apply(), update();
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
			// const float q = 1.05f;
			// const float s = m_scale;
			// const float w = m_width;
			// const float h = m_height;
			// const float m = fminf(w, h);
			// const float z2 = m_plane_far;
			// const float z1 = m_plane_near;
			// const float s1 = 2 * x1 / w - 1;
			// const float s2 = 1 - 2 * x2 / h;
			// const float sz = direction < 0 ? q : 1 / q;
			// //orthogonal
			// if(m_type == type::orthogonal)
			// {
			// 	//update fov
			// 	m_scale = sz * s;
			// 	//update position
			// 	m_position += m_rotation.rotate({(s - m_scale) * w / m * s1, (s - m_scale) * h / m * s2, 0});
			// }
			// //perspective
			// if(m_type == type::perspective)
			// {
			// 	// //data
			// 	// const float a = (z1 + z2) / (z2 - z1);
			// 	// const float b = -2 * z1 * z2 / (z2 - z1);
			// 	// //update fov
			// 	// m_fov = M_PI * sz * m_fov / (M_PI + (sz - 1) * m_fov);
			// 	// //update position
			// 	// const float tn = tan(m_fov / 2);
			// 	// const float sn = b / a / m * (tn - s);
			// 	// m_position += m_rotation.rotate({w * sn * s1, h * sn * s2, 0});
			// }
			// //apply
			// apply();
			// update();
		}
		void Camera::callback_special(canvas::key key, unsigned modifiers, int x1, int x2)
		{
			//data
			const float ds = 0.05f;
			const quat qn = m_rotation;
			const quat& qc = m_rotation;
			const float w = m_width;
			const float h = m_height;
			const float z2 = m_plane_far;
			const float z1 = m_plane_near;
			const float dt = float(M_PI) / 12;
			const vec3 shift[] = {{-ds, 0, 0}, {+ds, 0, 0}, {0, -ds, 0}, {0, +ds, 0}};
			const vec3 rotation[] = {{0, -dt, 0}, {0, +dt, 0}, {+dt, 0, 0}, {-dt, 0, 0}};
			const canvas::key keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
			//affine
			for(unsigned i = 0; i < 4; i++)
			{
				if(key == keys[i])
				{
					if(modifiers & 1 << unsigned(modifier::alt))
					{
						const float m = fminf(w, h);
						m_position -= qc.rotate(1.05 * mat4::scaling({w / m, h / m, 1}) * shift[i]);
					}
					else if(modifiers & 1 << unsigned(modifier::ctrl))
					{
						m_rotation = rotation[i].quaternion().conjugate() * m_rotation;
						m_position += (z1 + z2) / 2 * (qn.rotate({0, 0, 1}) - qc.rotate({0, 0, 1}));
					}
					else if(modifiers & 1 << unsigned(modifier::shift))
					{
						m_rotation = m_rotation * rotation[i].quaternion().conjugate();
						m_position += (z1 + z2) / 2 * (qn.rotate({0, 0, 1}) - qc.rotate({0, 0, 1}));
					}
					apply();
					update();
				}
			}
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
			const float s = m_scale;
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			const float z2 = m_plane_far;
			const float z1 = m_plane_near;
			//projection
			m_projection.clear();
			m_projection(0, 0) = +m / w / s;
			m_projection(1, 1) = +m / h / s;
			m_projection(2, 2) = -2 / (z2 - z1);
			m_projection(2, 3) = -(z1 + z2) / (z2 - z1);
		}
		void Camera::apply_perspective(void)
		{
			//data
			const float s = m_scale;
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			const float z2 = m_plane_far;
			const float z1 = m_plane_near;
			//projection
			m_projection.clear();
			m_projection(3, 3) = +0.0f;
			m_projection(3, 2) = -1.0f;
			m_projection(1, 1) = m / h / s;
			m_projection(0, 0) = m / w / s;
			m_projection(2, 2) = -(z1 + z2) / (z2 - z1);
			m_projection(2, 3) = -2 * z1 * z2 / (z2 - z1);
		}

		//bound
		void Camera::bound_orthogonal(void)
		{
			//data
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			const vec3 t1 = m_rotation.rotate({1.0f, 0.0f, 0.0f});
			const vec3 t2 = m_rotation.rotate({0.0f, 1.0f, 0.0f});
			const vec3 t3 = m_rotation.rotate({0.0f, 0.0f, 1.0f});
			//bound
			vec3 x_min, x_max;
			bound_center(x_min, x_max);
			//update
			m_plane_near = 1.0f;
			m_position[0] = (x_min[0] + x_max[0]) / 2;
			m_position[1] = (x_min[1] + x_max[1]) / 2;
			m_plane_far = m_plane_near + (x_max - x_min).norm();
			m_position[2] = m_plane_near + (x_max - x_min).norm() / 2 + (x_min[2] + x_max[2]) / 2;
			m_scale = fmaxf(m / w * (x_max[0] - x_min[0]) / 2, m / h * (x_max[1] - x_min[1]) / 2);
			m_position = m_rotation.rotate(m_position);
		}
		void Camera::bound_perspective(void)
		{
			//data
			const float s = m_scale;
			const float w = m_width;
			const float h = m_height;
			const float m = fminf(w, h);
			//bound
			vec3 x_min, x_max;
			bound_center(x_min, x_max);
			const float c1 = (x_min[0] + x_max[0]) / 2;
			const float c2 = (x_min[1] + x_max[1]) / 2;
			const float c3 = (x_min[2] + x_max[2]) / 2;
			const float s1 = (x_max[0] - x_min[0]) / 2;
			const float s2 = (x_max[1] - x_min[1]) / 2;
			//update
			m_position[0] = c1;
			m_position[1] = c2;
			m_position[2] = c3 + m / s * fmaxf(s1 / w, s2 / h);
			m_plane_far = m_position[2] - x_min[2];
			m_plane_near = m_position[2] - x_max[2];
			m_position = m_rotation.rotate(m_position);
		}
		void Camera::bound_center(vec3& x_min, vec3& x_max) const
		{
			//data
			const float a = FLT_MAX;
			const vec3 t1 = m_rotation.rotate({1.0f, 0.0f, 0.0f});
			const vec3 t2 = m_rotation.rotate({0.0f, 1.0f, 0.0f});
			const vec3 t3 = m_rotation.rotate({0.0f, 0.0f, 1.0f});
			//bound
			vec3 xm;
			x_min = {+a, +a, +a};
			x_max = {-a, -a, -a};
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < m_scene->m_vbo_size[i]; j++)
				{
					//position
					if(i == 2) xm = ((vertices::Text*) m_scene->m_vbo_data[i] + j)->m_position;
					if(i == 0) xm = ((vertices::Model*) m_scene->m_vbo_data[i] + j)->m_position;
					if(i == 1) xm = ((vertices::Image*) m_scene->m_vbo_data[i] + j)->m_position;
					//bound
					x_min[0] = fminf(x_min[0], xm.inner(t1));
					x_min[1] = fminf(x_min[1], xm.inner(t2));
					x_min[2] = fminf(x_min[2], xm.inner(t3));
					x_max[0] = fmaxf(x_max[0], xm.inner(t1));
					x_max[1] = fmaxf(x_max[1], xm.inner(t2));
					x_max[2] = fmaxf(x_max[2], xm.inner(t3));
				}
			}
			//check
			if(m_scene->objects().empty())
			{
				x_min = {-1.0f, -1.0f, -1.0f};
				x_max = {+1.0f, +1.0f, +1.0f};
			}
			for(unsigned i = 0; i < 3; i++)
			{
				if(x_min[i] == x_max[i])
				{
					x_min[i] -= 1.0f;
					x_max[i] += 1.0f;
				}
			}
		}
	}
}