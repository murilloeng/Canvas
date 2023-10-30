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
#include <filesystem>

//ext
#include "ext/inc/GL/glew.h"
#include "ext/inc/stb_image_write.h"

//canvas
#include "inc/GPU/Program.hpp"
#include "inc/Scene/Scene.hpp"
#include "inc/Scene/Camera.hpp"
#include "inc/Vertices/Text.hpp"
#include "inc/Vertices/Model.hpp"
#include "inc/Vertices/Image.hpp"

namespace canvas
{
	//constructors
	Camera::Camera(void) : m_mode(true), m_fov(M_PI_2), m_scale(1.0f), m_output("screen")
	{
		return;
	}

	//destructor
	Camera::~Camera(void)
	{
		return;
	}

	//data
	bool Camera::mode(void) const
	{
		return m_mode;
	}
	bool Camera::mode(bool mode)
	{
		return m_mode = mode;
	}

	float Camera::fov(float fov)
	{
		return m_fov = fov;
	}
	float Camera::fov(void) const
	{
		return m_fov;
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
			return rotation(quat::view_x1());
		}
		else if(mode == 'y')
		{
			return rotation(quat::view_x2());
		}
		else if(mode == 'z')
		{
			return rotation(quat::view_x3());
		}
		else if(mode == 'i')
		{
			static unsigned index = 1;
			return rotation(quat::view_iso(index = (index + 1) % 3));
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
		return m_screen[0];
	}
	unsigned Camera::height(void) const
	{
		return m_screen[1];
	}

	float Camera::plane(unsigned index) const
	{
		return m_planes[index];
	}
	float Camera::plane(unsigned index, float plane)
	{
		return m_planes[index] = plane;
	}

	//screen
	void Camera::screen_print(void) const
	{
		//data
		char path[200];
		unsigned index = 0;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
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
	void Camera::bound(void)
	{
		m_mode ? bound_orthogonal() : bound_perspective();
	}
	void Camera::update_shaders(void)
	{
		//data
		update_view();
		update_projection();
		const mat4 Mvp = m_projection_matrix * m_view_matrix;
		//update
		for(unsigned i = 0; i < 4; i++)
		{
			m_programs[i].use();
			glUniformMatrix4fv(m_programs[i].uniform("camera_matrix"), 1, false, Mvp.data());
		}
		m_programs[1].use();
		glUniform3fv(m_programs[1].uniform("camera_position"), 1, m_position.data());
	}

	//callbacks
	void Camera::callback_motion(int x1, int x2)
	{
		//data
		const float s = m_scale;
		const int w = m_screen[0];
		const int h = m_screen[1];
		const float m = fminf(w, h);
		const quat& qc = m_rotation;
		const int z1 = m_click.screen(0);
		const int z2 = m_click.screen(1);
		//shift
		if(m_click.button() == button::middle)
		{
			const float a1 = 2 * s * (x1 - z1) / m;
			const float a2 = 2 * s * (z2 - x2) / m;
			m_position = m_click.position() - qc.rotate({a1, a2, 0});
		}
		//rotation
		if(m_click.button() == button::left)
		{
			// const quat qc = m_click.rotation();
			// const vec3 v1 = Click::arcball(xc[0], xc[1]);
			// const vec3 v2 = Click::arcball(xp[0], xp[1]);
			// rotation((acosf(v1.inner(v2)) * v1.cross(v2).unit()).quaternion() * m_click.rotation());
			// shift(xp - m_rotation.rotate(m_click.rotation().conjugate().rotate(xc - m_click.shift())));
		}
		if(m_click.button() != button::none) update_shaders();
	}
	void Camera::callback_reshape(int width, int height)
	{
		//data
		m_screen[0] = width;
		m_screen[1] = height;
		//update
		bound();
		update_shaders();
		glViewport(0, 0, width, height);
	}
	void Camera::callback_wheel(int direction, int x1, int x2)
	{
		//data
		const float ds = 1.05;
		const float s = m_scale;
		const int w = m_screen[0];
		const int h = m_screen[1];
		const float m = fminf(w, h);
		const quat& qc = m_rotation;
		const float s1 = 2 * float(x1) / w - 1;
		const float s2 = 1 - 2 * float(x2) / h;
		//update
		m_scale = direction > 0 ? s / ds : s * ds;
		m_position -= (m_scale - s) * qc.rotate({w / m * s1, h / m * s2, 0});
		//shaders
		update_shaders();
	}
	void Camera::callback_special(canvas::key key, unsigned modifiers, int x1, int x2)
	{
		// //data
		// const float dx = 0.05;
		// const float dt = M_PI / 12;
		// const vec3 shift[] = {{-dx, 0, 0}, {+dx, 0, 0}, {0, -dx, 0}, {0, +dx, 0}};
		// const vec3 rotation[] = {{0, -dt, 0}, {0, +dt, 0}, {+dt, 0, 0}, {-dt, 0, 0}};
		// const canvas::key keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
		// //affine
		// for(unsigned i = 0; i < 4; i++)
		// {
		// 	if(key == keys[i])
		// 	{
		// 		if(modifiers & 1 << unsigned(modifier::alt))
		// 		{
		// 			this->shift(shift[i] + m_shift);
		// 		}
		// 		else if(modifiers & 1 << unsigned(modifier::ctrl))
		// 		{
		// 			this->rotation(rotation[i].quaternion() * m_rotation);
		// 		}
		// 		else if(modifiers & 1 << unsigned(modifier::shift))
		// 		{
		// 			this->rotation(m_rotation * rotation[i].quaternion());
		// 		}
		// 	}
		// }
	}
	void Camera::callback_keyboard(char key, int x1, int x2)
	{
		if(key == 'm') mode(!m_mode);
		if(key == 'p') screen_print();
		else if(key == 'f') bound(), update_shaders();
		else if(key == '-') callback_wheel(-1, m_screen[0] / 2, m_screen[1] / 2);
		else if(key == '+') callback_wheel(+1, m_screen[0] / 2, m_screen[1] / 2);
		// else if(key == 'x' || key == 'y' || key == 'z' || key == 'i') rotation(key);
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

	//update
	void Camera::update_view(void)
	{
		m_view_matrix = m_rotation.conjugate().rotation() * (-m_position).shift();
	}
	void Camera::update_projection(void)
	{
		m_mode ? update_orthogonal() : update_perspective();
	}
	void Camera::update_orthogonal(void)
	{
		//data
		const float s = m_scale;
		const float z1 = m_planes[0];
		const float z2 = m_planes[1];
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//projection
		m_projection_matrix(2, 2) = 2 / (z2 - z1);
		m_projection_matrix(0, 0) = fminf(w, h) / w / s;
		m_projection_matrix(1, 1) = fminf(w, h) / h / s;
		m_projection_matrix(2, 3) = -(z1 + z2) / (z2 - z1);
	}
	void Camera::update_perspective(void)
	{
		//data
		const float a = m_fov;
		const float s = m_scale;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		const float z1 = 1 / tanf(a / 2);
		const float z2 = 100 / tanf(a / 2) + 2;
		//projection
		m_projection_matrix(3, 3) = 0;
		m_projection_matrix(3, 2) = 1 / s;
		m_projection_matrix(2, 3) = -2 * z1 * z2 / (z2 - z1);
		m_projection_matrix(0, 0) = fminf(w, h) / w * z1 / s;
		m_projection_matrix(1, 1) = fminf(w, h) / h * z1 / s;
		m_projection_matrix(2, 2) = (z1 + z2) / (z2 - z1) / s;
	}

	//bound
	void Camera::bound_orthogonal(void)
	{
		//data
		const vec3& x1 = m_box_min;
		const vec3& x2 = m_box_max;
		const quat& qc = m_rotation;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//bound
		bound_box();
		vec3 xm = (x1 + x2) / 2;
		const vec3 xs = (x2 - x1) / 2;
		//apply
		m_planes[0] = 1;
		xm[0] *= w / fminf(w, h);
		xm[1] *= h / fminf(w, h);
		m_scale = fmaxf(xs[0], xs[1]);
		m_planes[1] = 1 + 2 * xs.norm();
		m_position = qc.rotate(xm - vec3(0, 0, m_planes[0] + xs.norm()));
	}
	void Camera::bound_perspective(void)
	{
		//data
		const vec3& x1 = m_box_min;
		const vec3& x2 = m_box_max;
		const quat& qc = m_rotation;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//bound
		bound_box();
		vec3 xm = (x1 + x2) / 2;
		const vec3 xs = (x2 - x1) / 2;
		m_scale = fmaxf(xs[0], fmaxf(xs[1], xs[2]));
		//apply
		xm[0] *= w / fminf(w, h);
		xm[1] *= h / fminf(w, h);
		const float z1 = 1 / tanf(m_fov / 2);
		m_position = qc.rotate(xm - m_scale * vec3(0, 0, 1 + z1));
	}
	void Camera::bound_box(void)
	{
		//data
		vec3 xw;
		const float a = FLT_MAX;
		const quat& qc = m_rotation;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//bound
		m_box_min = {+a, +a, +a};
		m_box_max = {-a, -a, -a};
		const float m = fminf(w, h);
		for(unsigned i = 0; i < 3; i++)
		{
			for(unsigned j = 0; j < m_scene->m_vbo_size[i]; j++)
			{
				//position
				if(i == 2) xw = qc.conjugate(((vertices::Text*) m_scene->m_vbo_data[i] + j)->m_position);
				if(i == 0) xw = qc.conjugate(((vertices::Model*) m_scene->m_vbo_data[i] + j)->m_position);
				if(i == 1) xw = qc.conjugate(((vertices::Image*) m_scene->m_vbo_data[i] + j)->m_position);
				//bouding box
				m_box_min[2] = fminf(m_box_min[2], xw[2]);
				m_box_max[2] = fmaxf(m_box_max[2], xw[2]);
				m_box_min[0] = fminf(m_box_min[0], m / w * xw[0]);
				m_box_max[0] = fmaxf(m_box_max[0], m / w * xw[0]);
				m_box_min[1] = fminf(m_box_min[1], m / h * xw[1]);
				m_box_max[1] = fmaxf(m_box_max[1], m / h * xw[1]);
			}
		}
	}
}