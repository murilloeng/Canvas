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
#include "inc/Scene/Camera.hpp"

namespace canvas
{
	//constructors
	Camera::Camera(void) : m_orthogonal(true), m_output("screen")
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
		for(unsigned i = 0; i < 4; i++)
		{
			m_programs[i].use();
			const unsigned location = glGetUniformLocation(m_programs[i].id(), "position");
			glUniform3f(location, position[0], position[1], position[2]);
		}
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
		for(unsigned i = 0; i < 4; i++)
		{
			m_programs[i].use();
			const unsigned location = glGetUniformLocation(m_programs[i].id(), "rotation");
			glUniform4f(location, rotation[0], rotation[1], rotation[2], rotation[3]);
		}
		return m_rotation = rotation;
	}

	bool Camera::orthogonal(void) const
	{
		return m_orthogonal;
	}
	bool Camera::orthogonal(bool orthogonal)
	{
		for(unsigned i = 0; i < 2; i++)
		{
			m_programs[i].use();
			glUniform1i(glGetUniformLocation(m_programs[i].id(), "camera_ortho"), orthogonal);
		}
		return m_orthogonal = orthogonal;
	}

	unsigned Camera::width(void) const
	{
		return m_screen[0];
	}
	unsigned Camera::height(void) const
	{
		return m_screen[1];
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
		m_screen[0] = width;
		m_screen[1] = height;
		glViewport(0, 0, width, height);
		for(unsigned i = 0; i < 4; i++)
		{
			m_programs[i].use();
			glUniform2ui(glGetUniformLocation(m_programs[i].id(), "screen"), width, height);
		}
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
		if(key == 'p') screen_print();
		if(key == 'o') orthogonal(!m_orthogonal);
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
}