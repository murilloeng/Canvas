//std
#include <cmath>
#include <chrono>
#include <thread>

//ext
#include "external/cpp/inc/GL/glew.h"
#include "external/cpp/inc/GL/freeglut.h"

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

//test
#include "Canvas/Test/inc/managers/Glut.hpp"

//static data
static Glut* master;
static std::chrono::high_resolution_clock::time_point t1, t2;

//constructors
Glut::Glut(int argc, char** argv, const char* shaders_dir) : m_show_fps(true), 
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
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	//window
	glutCreateWindow("Canvas");
	//glew
	if(glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Error: can't setup glew!\n");
		exit(EXIT_FAILURE);
	}
	m_scene = new canvas::Scene(shaders_dir);
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
bool Glut::show_fps(void) const
{
	return m_show_fps;
}
bool Glut::show_fps(bool show_fps)
{
	return m_show_fps = show_fps;
}
canvas::Scene* Glut::scene(void) const
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
void Glut::callback_keyboard(std::function<void(uint8_t, int, int)> callback_keyboard)
{
	m_callback_keyboard = callback_keyboard;
}

//loop
void Glut::start(void)
{
	t1 = std::chrono::high_resolution_clock::now();
	glutMainLoop();
}

//callbacks
void Glut::callback_idle(void)
{
	if(master->m_callback_idle)
	{
		master->m_callback_idle();
	}
	if(master->m_callback_idle || master->m_show_fps)
	{
		master->m_scene->draw();
		glutPostRedisplay();
	}
	if(master->m_show_fps)
	{
		using namespace std::chrono;
		t2 = high_resolution_clock::now();
		const uint64_t td = duration_cast<microseconds>(t2 - t1).count();
		printf("FPS: %d\n", uint32_t(1e6 / td));
		t1 = t2;
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
	uint32_t canvas_mod = 0;
	int glut_mod = glutGetModifiers();
	const uint32_t glut_keys[] = {GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_UP};
	const uint32_t glut_modifiers[] = {GLUT_ACTIVE_ALT, GLUT_ACTIVE_CTRL, GLUT_ACTIVE_SHIFT};
	const canvas::key canvas_keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
	const canvas::modifier canvas_modifiers[] = {canvas::modifier::alt, canvas::modifier::ctrl, canvas::modifier::shift};
	//master
	if(master->m_callback_special) master->m_callback_special(key, x1, x2);
	//callback
	for(uint32_t i = 0; i < 3; i++)
	{
		if(glut_mod & glut_modifiers[i])
		{
			canvas_mod |= 1 << uint32_t(canvas_modifiers[i]);
		}
	}
	for(uint32_t i = 0; i < 4; i++)
	{
		if(uint32_t(key) == glut_keys[i])
		{
			master->m_scene->camera().callback_special(canvas_keys[i], canvas_mod, x1, x2);
		}
	}
	glutPostRedisplay();
}
void Glut::callback_mouse(int button, int state, int x1, int x2)
{
	//data
	uint32_t glut_buttons[] = {GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON};
	canvas::button canvas_buttons[] = {canvas::button::left, canvas::button::right, canvas::button::middle};
	//callback
	for(uint32_t i = 0; i < 3; i++)
	{
		if(uint32_t(button) == glut_buttons[i])
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
void Glut::callback_keyboard(uint8_t key, int x1, int x2)
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
		for(canvas::objects::Object* object : master->m_scene->objects())
		{
			canvas::objects::Geometry* geometry = dynamic_cast<canvas::objects::Geometry*>(object);
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
		for(canvas::objects::Object* object : master->m_scene->objects())
		{
			canvas::objects::Geometry* geometry = dynamic_cast<canvas::objects::Geometry*>(object);
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

//data
uint32_t Glut::key_up = GLUT_KEY_UP;
uint32_t Glut::key_down = GLUT_KEY_DOWN;
uint32_t Glut::key_left = GLUT_KEY_LEFT;
uint32_t Glut::key_right = GLUT_KEY_RIGHT;