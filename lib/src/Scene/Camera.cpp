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
	Camera::Camera(void) : m_mode(true), m_planes{1.9, 3.9}, m_position{0, 0, -2}, m_output("screen")
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

	//shaders
	void Camera::bound(void)
	{
		m_mode ? bound_orthogonal() : bound_perspective();
	}
	void Camera::update_matrix(void)
	{
		m_mode ? matrix_orthogonal() : matrix_perspective();
	}
	void Camera::update_shaders(void) const
	{
		for(unsigned i = 0; i < 4; i++)
		{
			m_programs[i].use();
			glUniform3fv(glGetUniformLocation(m_programs[i].id(), "camera_position"), 1, m_position.memory());
			glUniformMatrix4fv(glGetUniformLocation(m_programs[i].id(), "camera_matrix"), 1, false, m_matrix.memory());
		}
	}

	//callbacks
	void Camera::callback_motion(int x1, int x2)
	{
		// //data
		// const float z = m_zoom;
		// const int w = m_screen[0];
		// const int h = m_screen[1];
		// const float m = w < h ? w : h;
		// const int z1 = m_click.position(0);
		// const int z2 = m_click.position(1);
		// const vec3 xp((2 * x1 - w) / m, (h - 2 * x2) / m, 0);
		// const vec3 xc((2 * z1 - w) / m, (h - 2 * z2) / m, 0);
		// //shift
		// if(m_click.button() == button::middle)
		// {
		// 	shift(m_click.shift() + xp - xc);
		// }
		// //rotation
		// if(m_click.button() == button::left)
		// {
		// 	const quat qc = m_click.rotation();
		// 	const vec3 v1 = Click::arcball(xc[0], xc[1]);
		// 	const vec3 v2 = Click::arcball(xp[0], xp[1]);
		// 	rotation((acosf(v1.inner(v2)) * v1.cross(v2).unit()).quaternion() * m_click.rotation());
		// 	shift(xp - m_rotation.rotate(m_click.rotation().conjugate().rotate(xc - m_click.shift())));
		// }
	}
	void Camera::callback_reshape(int width, int height)
	{
		//data
		m_screen[0] = width;
		m_screen[1] = height;
		//update
		bound();
		update_matrix();
		update_shaders();
		glViewport(0, 0, width, height);
	}
	void Camera::callback_wheel(int direction, int x1, int x2)
	{
		// //screen
		// const int w = m_screen[0];
		// const int h = m_screen[1];
		// const float m = w < h ? w : h;
		// const vec3 xs((2 * x1 - w) / m, (h - 2 * x2) / m, 0);
		// //affine
		// const float dz = 0.05;
		// zoom((1 + direction * dz) * m_zoom);
		// shift(xs - (1 + direction * dz) * (xs - m_shift));
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
		// else if(key == '-') zoom(m_zoom / 1.05);
		// else if(key == '+') zoom(m_zoom * 1.05);
		// else if(key == 'f') zoom(1.0f), shift(vec3()), rotation(quat());
		// else if(key == 'x' || key == 'y' || key == 'z' || key == 'i') rotation(key);
	}
	void Camera::callback_mouse(canvas::button button, bool pressed, int x1, int x2)
	{
		// if(pressed)
		// {
		// 	m_click.shift(m_shift);
		// 	m_click.button(button);
		// 	m_click.position(0, x1);
		// 	m_click.position(1, x2);
		// 	m_click.rotation(m_rotation);
		// }
		// else
		// {
		// 	m_click.button(canvas::button::none);
		// }
	}
	//affine
	void Camera::matrix_orthogonal(void)
	{
		//data
		mat4 A;
		const float z1 = m_planes[0];
		const float z2 = m_planes[1];
		const float dz = (z2 - z1) / 2;
		const float zm = (z1 + z2) / 2;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//camera
		A(2, 2) = 1 / dz;
		A(2, 3) = -zm / dz;
		A(0, 0) = fminf(w, h) / w / dz;
		A(1, 1) = fminf(w, h) / h / dz;
		m_matrix = A * m_rotation.conjugate().rotation() * (-m_position).shift();
	}
	void Camera::matrix_perspective(void)
	{
		//data
		mat4 A;
		const float z1 = m_planes[0];
		const float z2 = m_planes[1];
		const float dz = (z2 - z1) / 2;
		const float zm = (z1 + z2) / 2;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//camera
		A(3, 2) = 1;
		A(3, 3) = 0;
		A(2, 2) = zm / dz;
		A(2, 3) = -z1 * z2 / dz;
		A(0, 0) = fminf(w, h) / w * z1 / dz;
		A(1, 1) = fminf(w, h) / h * z1 / dz;
		m_matrix = A * m_rotation.conjugate().rotation() * (-m_position).shift();
	}

	//bound
	void Camera::bound_orthogonal(void)
	{
		//data
		vec3 x1, x2;
		bounding_box(x1, x2);
		const quat& qc = m_rotation;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//bound
		vec3 xm = (x1 + x2) / 2;
		const vec3 xs = (x2 - x1) / 2;
		const float dz = fmaxf(xs[0], fmaxf(xs[1], xs[2]));
		//apply
		m_planes[0] = dz;
		m_planes[1] = 3 * dz;
		xm[0] *= w / fminf(w, h);
		xm[1] *= h / fminf(w, h);
		m_position = qc.rotate(xm - 2 * dz * vec3(0, 0, 1));
	}
	void Camera::bound_perspective(void)
	{
		return;
	}
	void Camera::bounding_box(vec3& x1, vec3& x2)
	{
		//data
		vec3 xw;
		const float a = FLT_MAX;
		const quat& qc = m_rotation;
		const unsigned w = m_screen[0];
		const unsigned h = m_screen[1];
		//bound
		x1 = {+a, +a, +a};
		x2 = {-a, -a, -a};
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
				x1[2] = fminf(x1[2], xw[2]);
				x2[2] = fmaxf(x2[2], xw[2]);
				x1[0] = fminf(x1[0], m / w * xw[0]);
				x2[0] = fmaxf(x2[0], m / w * xw[0]);
				x1[1] = fminf(x1[1], m / h * xw[1]);
				x2[1] = fmaxf(x2[1], m / h * xw[1]);
			}
		}
	}
}