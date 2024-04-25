//std
#include <cmath>
#include <chrono>
#include <thread>

//ext
#include "external/cpp/inc/GL/glew.h"
#include "external/cpp/inc/GL/freeglut.h"

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Windows/Glut.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

//static data
canvas::windows::Glut* master;

namespace canvas
{
	namespace windows
	{
		//constructors
		Glut::Glut(int argc, char** argv, const char* shaders_dir) :
			m_callback_idle(nullptr), m_callback_special(nullptr), m_callback_keyboard(nullptr)
		{
			//glut
			master = this;
			glutInit(&argc, argv);
			glutInitWindowSize(700, 700);
			glutInitWindowPosition(0, 0);
			glutInitContextVersion(4, 6);
			glutInitContextProfile(GLUT_CORE_PROFILE);
			glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
			//window
			glutCreateWindow("Canvas");
			//glew
			if(glewInit() != GLEW_OK)
			{
				fprintf(stderr, "Error: can't setup glew!\n");
				exit(EXIT_FAILURE);
			}
			m_scene = new Scene(shaders_dir);
			//callbacks
			glutIdleFunc(callback_idle);
			glutMouseFunc(callback_mouse);
			glutMotionFunc(callback_motion);
			glutDisplayFunc(callback_display);
			glutReshapeFunc(callback_reshape);
			glutSpecialFunc(callback_special);
			glutMouseWheelFunc(callback_wheel);
			glutKeyboardFunc(callback_keyboard);
		}

		//destructor
		Glut::~Glut(void)
		{
			delete m_scene;
		}

		//data
		Scene* Glut::scene(void) const
		{
			return m_scene;
		}
		void Glut::callback_idle(std::function<void(void)> callback_idle)
		{
			m_callback_idle = callback_idle;
		}
		void Glut::callback_special(std::function<void(int, int, int)> callback_special)
		{
			m_callback_special = callback_special;
		}
		void Glut::callback_keyboard(std::function<void(unsigned char, int, int)> callback_keyboard)
		{
			m_callback_keyboard = callback_keyboard;
		}

		//loop
		void Glut::start(void)
		{
			glutMainLoop();
		}

		//callbacks
		void Glut::callback_idle(void)
		{
			if(master->m_callback_idle)
			{
				//idle
				master->m_callback_idle();
				//redraw
				glutPostRedisplay();
			}
		}
		void Glut::callback_display(void)
		{
			//draw
			master->m_scene->draw();
			//swap
			glutSwapBuffers();
		}
		void Glut::callback_motion(int x1, int x2)
		{
			master->m_scene->camera().callback_motion(x1, x2);
			glutPostRedisplay();
		}
		void Glut::callback_reshape(int width, int height)
		{
			master->m_scene->camera().callback_reshape(width, height);
			master->m_scene->update(true);
			glutPostRedisplay();
		}
		void Glut::callback_special(int key, int x1, int x2)
		{
			//data
			unsigned canvas_mod = 0;
			int glut_mod = glutGetModifiers();
			const unsigned glut_keys[] = {GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_UP};
			const unsigned glut_modifiers[] = {GLUT_ACTIVE_ALT, GLUT_ACTIVE_CTRL, GLUT_ACTIVE_SHIFT};
			const canvas::key canvas_keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
			const canvas::modifier canvas_modifiers[] = {canvas::modifier::alt, canvas::modifier::ctrl, canvas::modifier::shift};
			//master
			if(master->m_callback_special) master->m_callback_special(key, x1, x2);
			//callback
			for(unsigned i = 0; i < 3; i++)
			{
				if(glut_mod & glut_modifiers[i])
				{
					canvas_mod |= 1 << unsigned(canvas_modifiers[i]);
				}
			}
			for(unsigned i = 0; i < 4; i++)
			{
				if(unsigned(key) == glut_keys[i])
				{
					master->m_scene->camera().callback_special(canvas_keys[i], canvas_mod, x1, x2);
				}
			}
			glutPostRedisplay();
		}
		void Glut::callback_mouse(int button, int state, int x1, int x2)
		{
			//data
			unsigned glut_buttons[] = {GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON};
			canvas::button canvas_buttons[] = {canvas::button::left, canvas::button::right, canvas::button::middle};
			//callback
			for(unsigned i = 0; i < 3; i++)
			{
				if(unsigned(button) == glut_buttons[i])
				{
					master->m_scene->camera().callback_mouse(canvas_buttons[i], !state, x1, x2);
				}
			}
			glutPostRedisplay();
		}
		void Glut::callback_wheel(int, int direction, int x1, int x2)
		{
			master->m_scene->camera().callback_wheel(direction, x1, x2);
			glutPostRedisplay();
		}
		void Glut::callback_keyboard(unsigned char key, int x1, int x2)
		{
			//master
			if(master->m_callback_keyboard) master->m_callback_keyboard(key, x1, x2);
			//Canvas
			if(key == 27)
			{
				glutDestroyWindow(glutGetWindow());
			}
			else if(key == 't')
			{
				for(objects::Object* object : master->m_scene->objects())
				{
					objects::Geometry* geometry = dynamic_cast<objects::Geometry*>(object);
					if(geometry)
					{
						geometry->fill(!geometry->fill());
					}
				}
				master->scene()->update(true);
				glutPostRedisplay();
			}
			else if(key == 'l')
			{
				for(objects::Object* object : master->m_scene->objects())
				{
					objects::Geometry* geometry = dynamic_cast<objects::Geometry*>(object);
					if(geometry)
					{
						geometry->stroke(!geometry->stroke());
					}
				}
				master->scene()->update(true);
				glutPostRedisplay();
			}
			else if(key == 'a' || key == 'd' || key == 's')
			{
				master->m_scene->light().callback_keyboard(key, x1, x2);
				glutPostRedisplay();
			}
			else
			{
				master->m_scene->camera().callback_keyboard(key);
				glutPostRedisplay();
			}
		}
	}
}