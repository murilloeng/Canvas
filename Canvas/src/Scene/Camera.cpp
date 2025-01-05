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
#include "Canvas/Canvas/inc/GPU/Program.hpp"
#include "Canvas/Canvas/inc/Scene/Scene.hpp"
#include "Canvas/Canvas/inc/Scene/Camera.hpp"
#include "Canvas/Canvas/inc/Vertices/Text3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Model3D.hpp"
#include "Canvas/Canvas/inc/Vertices/Image3D.hpp"

namespace canvas
{
	namespace camera
	{

		//constructors
		Camera::Camera(Scene* scene) :
			m_scene(scene), m_type(camera::type::orthographic), 
			m_width(100), m_height(100), m_output("screen"), m_fov(float(M_PI) / 3), m_scale(1.0f), m_planes{1.0f, 2.0f}, m_programs(scene->m_programs)
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
				static uint32_t index = 1;
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

		uint32_t Camera::width(void) const
		{
			return m_width;
		}
		uint32_t Camera::width(uint32_t width)
		{
			return m_width = width;
		}

		uint32_t Camera::height(void) const
		{
			return m_height;
		}
		uint32_t Camera::height(uint32_t height)
		{
			return m_height = height;
		}

		float Camera::plane(uint32_t index) const
		{
			return m_planes[index];
		}
		float Camera::plane(uint32_t index, float plane)
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

		const mat4& Camera::view_matrix(void) const
		{
			return m_view_matrix;
		}
		const mat4& Camera::projection_matrix(void) const
		{
			return m_projection_matrix;
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

		//update
		void Camera::apply(void)
		{
			apply_view();
			m_type == camera::type::orthographic ? apply_orthographic() : apply_perspective();
		}
		void Camera::bound(void)
		{
			bound_box();
			bound_check();
			bound_limits();
			m_type == camera::type::orthographic ? bound_orthographic() : bound_perspective();
		}
		void Camera::update(void)
		{
			for(const Program* program : m_programs)
			{
				program->bind();
				if(program->uniform_location("width") != -1)
				{
					program->set_uniform("width", m_width);
				}
				if(program->uniform_location("height") != -1)
				{
					program->set_uniform("height", m_height);
				}
				if(program->uniform_location("view") != -1)
				{
					program->set_uniform("view", m_view_matrix);
				}
				if(program->uniform_location("projection") != -1)
				{
					program->set_uniform("projection", m_projection_matrix);
				}
				if(program->uniform_location("camera_position") != -1)
				{
					program->set_uniform("camera_position", m_position);
				}
			}
		}

		//callbacks
		void Camera::callback_keyboard(char key)
		{
			if(key == 'p') screen_print();
			else if(key == '-') callback_wheel(-1, m_width / 2, m_height / 2);
			else if(key == '+') callback_wheel(+1, m_width / 2, m_height / 2);
			else if(key == 'f') m_fov = float(M_PI) / 3, bound(), apply(), update();
			else if(key == 'c') m_type = camera::type(!uint32_t(m_type)), bound(), apply(), update();
			else if(key == 'x' || key == 'y' || key == 'z' || key == 'i') rotation(key), bound(), apply(), update(), m_scene->update_on_motion();
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
			if(m_click.button() != button::none) apply(), update(), m_scene->update_on_motion();
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
			//orthographic
			if(m_type == type::orthographic)
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
		void Camera::callback_special(canvas::key key, uint32_t modifiers, int x1, int x2)
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
			for(uint32_t i = 0; i < 4; i++)
			{
				if(key == keys[i])
				{
					if(modifiers & 1 << uint32_t(modifier::alt))
					{
						const float ms = fminf(ws, hs);
						m_position -= m_rotation.rotate(m_scale * mat4::scaling({ws / ms, hs / ms, 1}) * shift[i]);
					}
					else if(modifiers & 1 << uint32_t(modifier::ctrl))
					{
						m_rotation = rotation[i].quaternion().conjugate() * m_rotation;
						m_position += (z1 + z2) / 2 * (m_rotation.rotate({0, 0, 1}) - qn.rotate({0, 0, 1}));
					}
					else if(modifiers & 1 << uint32_t(modifier::shift))
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
			m_view_matrix = m_rotation.conjugate().rotation() * (-m_position).shift();
		}
		void Camera::apply_perspective(void)
		{
			//data
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float ts = tanf(m_fov / 2);
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			//projection
			m_projection_matrix.clear();
			m_projection_matrix(3, 3) = +0.0f;
			m_projection_matrix(3, 2) = -1.0f;
			m_projection_matrix(0, 0) = ms / ws / ts;
			m_projection_matrix(1, 1) = ms / hs / ts;
			m_projection_matrix(2, 2) = -(z1 + z2) / (z2 - z1);
			m_projection_matrix(2, 3) = -2 * z1 * z2 / (z2 - z1);
		}
		void Camera::apply_orthographic(void)
		{
			//data
			const float s = m_scale;
			const float z1 = m_planes[0];
			const float z2 = m_planes[1];
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			//projection
			m_projection_matrix.clear();
			m_projection_matrix(0, 0) = ms / ws / s;
			m_projection_matrix(1, 1) = ms / hs / s;
			m_projection_matrix(2, 2) = -2 / (z2 - z1);
			m_projection_matrix(2, 3) = -(z1 + z2) / (z2 - z1);
		}

		//bound
		void Camera::bound_box(void)
		{
			//data
			const float a = FLT_MAX;
			const vec3 t1 = m_rotation.rotate({1.0f, 0.0f, 0.0f});
			const vec3 t2 = m_rotation.rotate({0.0f, 1.0f, 0.0f});
			const vec3 t3 = m_rotation.rotate({0.0f, 0.0f, 1.0f});
			//bound
			const vec3* xp;
			m_x_min = {+a, +a, +a};
			m_x_max = {-a, -a, -a};
			for(uint32_t i = 0; i < 3; i++)
			{
				for(uint32_t j = 0; j < m_scene->m_vbos[i]->size(); j++)
				{
					//position
					if(i == 2) xp = &((vertices::Text3D*) m_scene->m_vbos[i]->data() + j)->m_position;
					else if(i == 0) xp = &((vertices::Model3D*) m_scene->m_vbos[i]->data() + j)->m_position;
					else if(i == 1) xp = &((vertices::Image3D*) m_scene->m_vbos[i]->data() + j)->m_position;
					//bound
					m_x_min[0] = fminf(m_x_min[0], xp->inner(t1));
					m_x_min[1] = fminf(m_x_min[1], xp->inner(t2));
					m_x_min[2] = fminf(m_x_min[2], xp->inner(t3));
					m_x_max[0] = fmaxf(m_x_max[0], xp->inner(t1));
					m_x_max[1] = fmaxf(m_x_max[1], xp->inner(t2));
					m_x_max[2] = fmaxf(m_x_max[2], xp->inner(t3));
				}
			}
		}
		void Camera::bound_check(void)
		{
			//data
			const bool test_size = 
				!m_scene->m_vbos[0]->size() && 
				!m_scene->m_vbos[1]->size() && 
				!m_scene->m_vbos[2]->size();
			const bool test_point =
				m_x_min[0] == m_x_max[0] && m_x_min[1] == m_x_max[1] && m_x_min[2] == m_x_max[2];
			//size
			if(test_size)
			{
				m_x_min = {-1.0f, -1.0f, -1.0f};
				m_x_max = {+1.0f, +1.0f, +1.0f};
			}
			//point
			if(test_point)
			{
				m_x_min[0] -= 1; m_x_min[1] -= 1; m_x_min[2] -= 1;
				m_x_max[0] += 1; m_x_max[1] += 1; m_x_max[2] += 1;
			}
		}
		void Camera::bound_limits(void)
		{
			//data
			const vec3* xp;
			const float* x1 = m_x_min.data();
			const float* x2 = m_x_max.data();
			const float s = (m_x_max - m_x_min).norm();
			const vec3 t1 = m_rotation.rotate({1.0f, 0.0f, 0.0f});
			const vec3 t2 = m_rotation.rotate({0.0f, 1.0f, 0.0f});
			const vec3 t3 = m_rotation.rotate({0.0f, 0.0f, 1.0f});
			//bounds
			m_bounds.clear();
			for(uint32_t i = 0; i < 3; i++)
			{
				for(uint32_t j = 0; j < m_scene->m_vbos[i]->size(); j++)
				{
					//position
					if(i == 2) xp = &((vertices::Text3D*) m_scene->m_vbos[i]->data() + j)->m_position;
					if(i == 0) xp = &((vertices::Model3D*) m_scene->m_vbos[i]->data() + j)->m_position;
					if(i == 1) xp = &((vertices::Image3D*) m_scene->m_vbos[i]->data() + j)->m_position;
					//update
					const vec3 xs(xp->inner(t1), xp->inner(t2), xp->inner(t3));
					const bool c1 = fabs(xs[0] - x1[0]) < 1e-5 * s || fabs(xs[0] - x2[0]) < 1e-5 * s;
					const bool c2 = fabs(xs[1] - x1[1]) < 1e-5 * s || fabs(xs[1] - x2[1]) < 1e-5 * s;
					const bool c3 = fabs(xs[2] - x1[2]) < 1e-5 * s || fabs(xs[2] - x2[2]) < 1e-5 * s;
					if(c1 || c2 || c3) m_bounds.push_back(xs);
				}
			}
		}
		void Camera::bound_search_1(void)
		{
			//data
			float s1_min = +FLT_MAX;
			float s1_max = -FLT_MAX;
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			//search
			for(const vec3& x : m_bounds)
			{
				s1_min = fminf(s1_min, x[0] + ws * m_scale / ms * (m_position[2] - x[2]));
				s1_max = fmaxf(s1_max, x[0] - ws * m_scale / ms * (m_position[2] - x[2]));
			}
			//position
			m_position[0] = (s1_min + s1_max) / 2;
		}
		void Camera::bound_search_2(void)
		{
			//data
			float s2_min = +FLT_MAX;
			float s2_max = -FLT_MAX;
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			//search
			for(const vec3& x : m_bounds)
			{
				s2_min = fminf(s2_min, x[1] + hs * m_scale / ms * (m_position[2] - x[2]));
				s2_max = fmaxf(s2_max, x[1] - hs * m_scale / ms * (m_position[2] - x[2]));
			}
			//position
			m_position[1] = (s2_min + s2_max) / 2;
		}
		void Camera::bound_bisection_1(void)
		{
			//data
			float fn, sn;
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			const float dx1 = m_x_max[0] - m_x_min[0];
			const float ds3 = m_position[2] - m_x_max[2];
			//setup
			float s1 = 0;
			float s2 = ms / ws / 2 * dx1 / ds3;
			float f1 = bound_bisection_1(s1);
			float f2 = bound_bisection_1(s2);
			if(fabsf(f1) < 1e-5 * dx1) { m_scale = fmaxf(m_scale, s1); return; };
			if(fabsf(f2) < 1e-5 * dx1) { m_scale = fmaxf(m_scale, s2); return; };
			//bisection
			while(true)
			{
				sn = (s1 + s2) / 2;
				fn = bound_bisection_1(sn);
				if(fabsf(fn) < 1e-5 * dx1) break;
				if(f1 * fn > 0) { s1 = sn, f1 = fn; }
				if(f2 * fn > 0) { s2 = sn, f2 = fn; }
			}
			//update
			m_scale = fmaxf(m_scale, sn);
		}
		void Camera::bound_bisection_2(void)
		{
			//data
			float fn, sn;
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			const float dx2 = m_x_max[1] - m_x_min[1];
			const float ds3 = m_position[2] - m_x_max[2];
			//setup
			float s1 = 0;
			float s2 = ms / hs / 2 * dx2 / ds3;
			float f1 = bound_bisection_2(s1);
			float f2 = bound_bisection_2(s2);
			if(fabsf(f1) < 1e-5 * dx2) { m_scale = fmaxf(m_scale, s1); return; };
			if(fabsf(f2) < 1e-5 * dx2) { m_scale = fmaxf(m_scale, s2); return; };
			//bisection
			while(true)
			{
				sn = (s1 + s2) / 2;
				fn = bound_bisection_2(sn);
				if(fabsf(fn) < 1e-5 * dx2) break;
				if(f1 * fn > 0) { s1 = sn, f1 = fn; }
				if(f2 * fn > 0) { s2 = sn, f2 = fn; }
			}
			//update
			m_scale = fmaxf(m_scale, sn);
		}
		void Camera::bound_perspective(void)
		{
			//planes
			m_planes[0] = 1.0f;
			m_planes[1] = m_planes[0] + (m_x_max - m_x_min).norm();
			m_position[2] = (m_x_min[2] + m_x_max[2]) / 2 + (m_planes[0] + m_planes[1]) / 2;
			//scale
			m_scale = 0;
			bound_bisection_1();
			bound_bisection_2();
			//update
			bound_search_1();
			bound_search_2();
			m_fov = 2 * atan(m_scale);
			m_position = m_rotation.rotate(m_position);
		}
		void Camera::bound_orthographic(void)
		{
			//data
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			//planes
			m_planes[0] = 1.0f;
			m_planes[1] = m_planes[0] + (m_x_max - m_x_min).norm();
			//position
			m_position[0] = (m_x_min[0] + m_x_max[0]) / 2;
			m_position[1] = (m_x_min[1] + m_x_max[1]) / 2;
			m_position[2] = (m_x_min[2] + m_x_max[2]) / 2 + (m_planes[0] + m_planes[1]) / 2;
			//scale
			const float ms = fminf(ws, hs);
			const float s1 = ms / ws * (m_x_max[0] - m_x_min[0]) / 2;
			const float s2 = ms / hs * (m_x_max[1] - m_x_min[1]) / 2;
			//bound
			m_scale = fmaxf(s1, s2);
			m_position = m_rotation.rotate(m_position);
		}
		float Camera::bound_bisection_1(float s)
		{
			//data
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			//function
			float f_min = +FLT_MAX;
			float f_max = -FLT_MAX;
			for(const vec3& x : m_bounds)
			{
				f_min = fminf(f_min, x[0] + ws / ms * s * (m_position[2] - x[2]));
				f_max = fmaxf(f_max, x[0] - ws / ms * s * (m_position[2] - x[2]));
			}
			//return
			return f_max - f_min;
		}
		float Camera::bound_bisection_2(float s)
		{
			//data
			const float ws = (float) m_width;
			const float hs = (float) m_height;
			const float ms = ws < hs ? ws : hs;
			//function
			float f_min = +FLT_MAX;
			float f_max = -FLT_MAX;
			for(const vec3& x : m_bounds)
			{
				f_min = fminf(f_min, x[1] + hs / ms * s * (m_position[2] - x[2]));
				f_max = fmaxf(f_max, x[1] - hs / ms * s * (m_position[2] - x[2]));
			}
			//return
			return f_max - f_min;
		}
	}
}