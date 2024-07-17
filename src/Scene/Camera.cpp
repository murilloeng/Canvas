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
#include "Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/inc/Vertices/Image3D.hpp"

namespace canvas
{
	namespace camera
	{

		//constructors
		Camera::Camera(void) :
			m_type(camera::type::orthogonal), m_width(100), m_height(100), m_fov(float(M_PI) / 3), m_scale(1.0f), m_planes{1.0f, 2.0f}, m_output("screen")
		{
			return;
		}

		//destructor
		Camera::~Camera(void)
		{
			return;
		}

		//data
		float Camera::fov(float fov)
		{
			return m_fov = fov;
		}
		float Camera::fov(void) const
		{
			return m_fov;
		}


		vec3 Camera::x_min(vec3 x_min)
		{
			return m_x_min = x_min;
		}
		vec3 Camera::x_min(void) const
		{
			return m_x_min;
		}

		vec3 Camera::x_max(vec3 x_max)
		{
			return m_x_max = x_max;
		}
		vec3 Camera::x_max(void) const
		{
			return m_x_max;
		}

		float Camera::scale(void) const
		{
			return m_scale;
		}
		float Camera::scale(float scale)
		{
			return m_scale = scale;
		}

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

		float Camera::plane(unsigned index) const
		{
			return m_planes[index];
		}
		float Camera::plane(unsigned index, float plane)
		{
			return m_planes[index] = plane;
		}

		camera::type Camera::type(void) const
		{
			return m_type;
		}
		camera::type Camera::type(camera::type type)
		{
			return m_type = type;
		}

		const mat4& Camera::view(void) const
		{
			return m_view;
		}
		const mat4& Camera::projection(void) const
		{
			return m_projection;
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
			bound_center();
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
			else if(key == '-') callback_wheel(-1, m_width / 2, m_height / 2);
			else if(key == '+') callback_wheel(+1, m_width / 2, m_height / 2);
			else if(key == 'f') m_fov = float(M_PI) / 3, bound(), apply(), update();
			else if(key == 'c') m_type = camera::type(!unsigned(m_type)), bound(),apply(), update();
			else if(key == 'x' || key == 'y' || key == 'z' || key == 'i') rotation(key), bound(), apply(), update();
		}
		void Camera::callback_motion(int x1, int x2)
		{
			//data
			const float s = m_scale;
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float w = (float) m_width;
			const float h = (float) m_height;
			const int a1 = m_click.screen(0);
			const int a2 = m_click.screen(1);
			const vec3 xc = m_click.position();
			const quat qc = m_click.rotation();
			//data
			const float m = fminf(w, h);
			const vec3 v1 = Click::arcball((2 * a1 - w) / m, (h - 2 * a2) / m);
			const vec3 v2 = Click::arcball((2 * x1 - w) / m, (h - 2 * x2) / m);
			//shift
			if(m_click.button() == button::middle)
			{
				const float b1 = 2 * s / m * (a1 - x1);
				const float b2 = 2 * s / m * (x2 - a2);
				m_position = xc + m_rotation.rotate({b1, b2, 0});
			}
			//rotation
			if(m_click.button() == button::left)
			{
				m_rotation = qc * Click::arcball(v1, v2).conjugate();
				m_position = xc + (z1 + z2) / 2 * (m_rotation.rotate({0, 0, 1}) - qc.rotate({0, 0, 1}));
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
			//data
			const float q = 1.05f;
			const float s = m_scale;
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			//data
			const float m = fminf(ws, hs);
			const float s1 = 2 * x1 / ws - 1;
			const float s2 = 1 - 2 * x2 / hs;
			const float sz = direction < 0 ? q : 1 / q;
			//orthogonal
			if(m_type == type::orthogonal)
			{
				//update fov
				m_scale = sz * s;
				//update position
				m_position += m_rotation.rotate({(s - m_scale) * ws / m * s1, (s - m_scale) * hs / m * s2, 0});
			}
			//perspective
			if(m_type == type::perspective)
			{
				//data
				const float p = float(M_PI);
				const float t = tanf(m_fov / 2);
				const float a = (z1 + z2) / (z2 - z1);
				const float b = -2 * z1 * z2 / (z2 - z1);
				//update fov
				m_fov = p * sz * m_fov / (p + (sz - 1) * m_fov);
				//update position
				const float tn = tan(m_fov / 2);
				const float sn = b / a / m * (tn - t);
				m_position += m_rotation.rotate({ws * sn * s1, hs * sn * s2, 0});
			}
			//apply
			apply();
			update();
		}
		void Camera::callback_special(canvas::key key, unsigned modifiers, int x1, int x2)
		{
			//data
			const float ds = 0.05f;
			const quat qn = m_rotation;
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float dt = (float) M_PI / 12;
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
						const float ms = fminf(ws, hs);
						m_position -= m_rotation.rotate(m_scale * mat4::scaling({ws / ms, hs / ms, 1}) * shift[i]);
					}
					else if(modifiers & 1 << unsigned(modifier::ctrl))
					{
						m_rotation = rotation[i].quaternion().conjugate() * m_rotation;
						m_position += (z1 + z2) / 2 * (m_rotation.rotate({0, 0, 1}) - qn.rotate({0, 0, 1}));
					}
					else if(modifiers & 1 << unsigned(modifier::shift))
					{
						m_rotation = m_rotation * rotation[i].quaternion().conjugate();
						m_position += (z1 + z2) / 2 * (m_rotation.rotate({0, 0, 1}) - qn.rotate({0, 0, 1}));
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
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = fminf(ws, hs);
			//projection
			m_projection.clear();
			m_projection(0, 0) = +ms / ws / s;
			m_projection(1, 1) = +ms / hs / s;
			m_projection(2, 2) = -2 / (z2 - z1);
			m_projection(2, 3) = -(z1 + z2) / (z2 - z1);
		}
		void Camera::apply_perspective(void)
		{
			//data
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			//data
			const float ms = fminf(ws, hs);
			const float ts = tanf(m_fov / 2);
			//projection
			m_projection.clear();
			m_projection(3, 3) = +0.0f;
			m_projection(3, 2) = -1.0f;
			m_projection(0, 0) = ms / ws / ts;
			m_projection(1, 1) = ms / hs / ts;
			m_projection(2, 2) = -(z1 + z2) / (z2 - z1);
			m_projection(2, 3) = -2 * z1 * z2 / (z2 - z1);
		}

		//bound
		void Camera::bound_center(void)
		{
			//data
			const float a = FLT_MAX;
			const vec3 t1 = m_rotation.rotate({1.0f, 0.0f, 0.0f});
			const vec3 t2 = m_rotation.rotate({0.0f, 1.0f, 0.0f});
			const vec3 t3 = m_rotation.rotate({0.0f, 0.0f, 1.0f});
			//bound
			const vec3* xm;
			m_x_min = {+a, +a, +a};
			m_x_max = {-a, -a, -a};
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < m_scene->m_vbo_size[i]; j++)
				{
					//position
					if(i == 2) xm = &((vertices::Text3D*) m_scene->m_vbo_data[i] + j)->m_position;
					if(i == 0) xm = &((vertices::Model3D*) m_scene->m_vbo_data[i] + j)->m_position;
					if(i == 1) xm = &((vertices::Image3D*) m_scene->m_vbo_data[i] + j)->m_position;
					//bound
					m_x_min[0] = fminf(m_x_min[0], xm->inner(t1));
					m_x_min[1] = fminf(m_x_min[1], xm->inner(t2));
					m_x_min[2] = fminf(m_x_min[2], xm->inner(t3));
					m_x_max[0] = fmaxf(m_x_max[0], xm->inner(t1));
					m_x_max[1] = fmaxf(m_x_max[1], xm->inner(t2));
					m_x_max[2] = fmaxf(m_x_max[2], xm->inner(t3));
				}
			}
			//check
			if(m_scene->objects().empty())
			{
				m_x_min = {-1.0f, -1.0f, -1.0f};
				m_x_max = {+1.0f, +1.0f, +1.0f};
			}
		}
		void Camera::bound_orthogonal(void)
		{
			//data
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const vec3 t1 = m_rotation.rotate({1.0f, 0.0f, 0.0f});
			const vec3 t2 = m_rotation.rotate({0.0f, 1.0f, 0.0f});
			const vec3 t3 = m_rotation.rotate({0.0f, 0.0f, 1.0f});
			//bound
			const float ms = fminf(ws, hs);
			for(unsigned i = 0; i < 3; i++)
			{
				if(m_x_min[i] == m_x_max[i])
				{
					m_x_min[i] -= 1.0f;
					m_x_max[i] += 1.0f;
				}
			}
			//planes
			m_planes[0] = 1.0f;
			m_planes[1] = m_planes[0] + (m_x_max - m_x_min).norm();
			//position
			m_position[0] = (m_x_min[0] + m_x_max[0]) / 2;
			m_position[1] = (m_x_min[1] + m_x_max[1]) / 2;
			m_position[2] = (m_x_min[2] + m_x_max[2]) / 2 + (m_planes[0] + m_planes[1]) / 2;
			//bound
			m_position = m_rotation.rotate(m_position);
			m_scale = fmaxf(ms / ws * (m_x_max[0] - m_x_min[0]) / 2, ms / hs * (m_x_max[1] - m_x_min[1]) / 2);
		}
		void Camera::bound_perspective(void)
		{
			//data
			const float ts = tanf(m_fov / 2);
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const vec3 t1 = m_rotation.rotate({1.0f, 0.0f, 0.0f});
			const vec3 t2 = m_rotation.rotate({0.0f, 1.0f, 0.0f});
			const vec3 t3 = m_rotation.rotate({0.0f, 0.0f, 1.0f});
			//bound
			m_position[0] = (m_x_min[0] + m_x_max[0]) / 2;
			m_position[1] = (m_x_min[1] + m_x_max[1]) / 2;
			m_position[2] = (m_x_min[2] + m_x_max[2]) / 2;
			//position
			const float ms = fminf(ws, hs);
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < m_scene->m_vbo_size[i]; j++)
				{
					//position
					const vec3* xm;
					if(i == 2) xm = &((vertices::Text3D*) m_scene->m_vbo_data[i] + j)->m_position;
					if(i == 0) xm = &((vertices::Model3D*) m_scene->m_vbo_data[i] + j)->m_position;
					if(i == 1) xm = &((vertices::Image3D*) m_scene->m_vbo_data[i] + j)->m_position;
					//bound
					const float x1 = xm->inner(t1);
					const float x2 = xm->inner(t2);
					const float x3 = xm->inner(t3);
					m_position[2] = fmaxf(m_position[2], x3 + ms / ws / ts * fabs(x1 - m_position[0]));
					m_position[2] = fmaxf(m_position[2], x3 + ms / hs / ts * fabs(x2 - m_position[1]));
				}
			}
			//planes
			m_planes[0] = m_position[2] - m_x_max[2] - (m_x_max[2] == m_x_min[2]) * m_position[2] / 2;
			m_planes[1] = m_position[2] - m_x_min[2] + (m_x_max[2] == m_x_min[2]) * m_position[2] / 2;
			m_position = m_rotation.rotate(m_position);
		}
	}
}