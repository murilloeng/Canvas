//std
#include "../external/cpp/inc/GL/glew.h"
#include "../external/cpp/inc/GL/freeglut.h"

//canvas
#include "inc/Scene/Scene.hpp"
#include "inc/Managers/Glut.hpp"

//static data
canvas::Glut* master;

namespace canvas
{
	//constructors
	Glut::Glut(int argc, char** argv)
	{
		//glut
		master = this;
		glutInit(&argc, argv);
		glutInitWindowSize(700, 700);
		glutInitWindowPosition(0, 0);
		glutInitContextVersion(4, 6);
		glutInitContextProfile(GLUT_CORE_PROFILE);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
		//window
		glutCreateWindow("Canvas");
		//glew
		if(glewInit() != GLEW_OK)
		{
			printf("Error: can't setup glew!\n");
			exit(EXIT_FAILURE);
		}
		//callbacks
		m_scene = new Scene;
		glutMouseFunc(callback_mouse);
		glutMotionFunc(callback_motion);
		glutDisplayFunc(callback_display);
		glutReshapeFunc(callback_reshape);
		glutSpecialFunc(callback_special);
		glutMouseWheelFunc(callback_wheel);
		glutKeyboardFunc(callback_keyboard);
		glutPassiveMotionFunc(callback_motion);
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

	//loop
	void Glut::start(void)
	{
		glutMainLoop();
	}

	//callbacks
	void Glut::callback_display(void)
	{
		//draw
		master->scene()->draw();
		//swap
		glutSwapBuffers();
	}
	void Glut::callback_motion(int x1, int x2)
	{
		master->scene()->camera().callback_motion(x1, x2);
		glutPostRedisplay();
	}
	void Glut::callback_reshape(int width, int height)
	{
		master->scene()->camera().callback_reshape(width, height);
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
			if(key == glut_keys[i])
			{
				master->scene()->camera().callback_special(canvas_keys[i], canvas_mod, x1, x2);
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
			if(glut_buttons[i] == button)
			{
				master->scene()->camera().callback_mouse(canvas_buttons[i], !state, x1, x2);
			}
		}
		glutPostRedisplay();
	}
	void Glut::callback_wheel(int, int direction, int x1, int x2)
	{
		master->scene()->camera().callback_wheel(direction, x1, x2);
		glutPostRedisplay();
	}
	void Glut::callback_keyboard(unsigned char key, int x1, int x2)
	{
		if(key == 27)
		{
			glutDestroyWindow(glutGetWindow());
		}
		else
		{
			master->scene()->camera().callback_keyboard(key, x1, x2);
			master->scene()->update(false);
			glutPostRedisplay();
		}
	}
}