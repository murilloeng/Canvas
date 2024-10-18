//std
#include <cmath>
#include <chrono>
#include <thread>

//canvas
#include "Canvas/inc/Scene/Scene.hpp"
#include "Canvas/inc/Objects/Geometry.hpp"

//test
#include "Canvas/Test/inc/managers/GLFW.hpp"

//static data
static GLFW* master;
static std::chrono::high_resolution_clock::time_point t1, t2;

//constructors
GLFW::GLFW(int argc, char** argv, const char* shaders_dir) : m_show_fps(true), 
	m_callback_idle(nullptr), m_callback_special(nullptr), m_callback_keyboard(nullptr)
{
	//setup
	master = this;
	if(!glfwInit())
	{
		fprintf(stderr, "Error: Unable to initialize GLFW!\n");
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//window
	m_window = glfwCreateWindow(700, 700, "Canvas", nullptr, nullptr);
	if(!m_window)
	{
		glfwTerminate();
		fprintf(stderr, "Error: Unable to create GLFW window!\n");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(m_window);
	glfwSetWindowPos(m_window, 200, 200);
	//glew
	if(glewInit() != GLEW_OK)
	{
		glfwTerminate();
		fprintf(stderr, "Error: can't setup glew!\n");
		exit(EXIT_FAILURE);
	}
	m_scene = new canvas::Scene(shaders_dir);
	//callbacks
	glfwSetKeyCallback(m_window, callback_key);
	glfwSetWindowSizeCallback(m_window, callback_size);
	// glutIdleFunc(callback_idle);
	// glutMouseFunc(callback_mouse);
	// glutMotionFunc(callback_motion);
	// glutSpecialFunc(callback_special);
	// glutMouseWheelFunc(callback_wheel);
	// glutKeyboardFunc(callback_keyboard);
}

//destructor
GLFW::~GLFW(void)
{
	//scene
	delete m_scene;
	//window
	glfwDestroyWindow(m_window);
	//library
	glfwTerminate();
}

//data
bool GLFW::show_fps(void) const
{
	return m_show_fps;
}
bool GLFW::show_fps(bool show_fps)
{
	return m_show_fps = show_fps;
}
canvas::Scene* GLFW::scene(void) const
{
	return m_scene;
}
void GLFW::callback_idle(std::function<void(void)> callback_idle)
{
	m_callback_idle = callback_idle;
}
void GLFW::callback_special(std::function<void(int, int, int)> callback_special)
{
	m_callback_special = callback_special;
}
void GLFW::callback_keyboard(std::function<void(uint8_t, int, int)> callback_keyboard)
{
	m_callback_keyboard = callback_keyboard;
}

//loop
void GLFW::start(void)
{
	t1 = std::chrono::high_resolution_clock::now();
	while(!glfwWindowShouldClose(m_window))
	{
		if(master->m_callback_idle)
		{
			master->m_callback_idle();
		}
		if(master->m_callback_idle || master->m_show_fps)
		{
			master->m_scene->draw();
			glfwSwapBuffers(m_window);
		}
		if(master->m_show_fps)
		{
			using namespace std::chrono;
			t2 = high_resolution_clock::now();
			const uint64_t td = duration_cast<microseconds>(t2 - t1).count();
			printf("FPS: %d\n", uint32_t(1e6 / td));
			t1 = t2;
		}
		glfwPollEvents();
	}
}

//callbacks
void GLFW::callback_motion(int x1, int x2)
{
	// master->m_scene->camera().callback_motion(x1, x2);
	// glutPostRedisplay();
}
void GLFW::callback_size(GLFWwindow* window, int width, int height)
{
	master->m_scene->camera().callback_reshape(width, height);
	master->m_scene->update(true);
	glfwSwapBuffers(window);
}
void GLFW::callback_special(int key, int x1, int x2)
{
	// //data
	// uint32_t canvas_mod = 0;
	// int glut_mod = glutGetModifiers();
	// const uint32_t glut_keys[] = {GLUT_KEY_LEFT, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_UP};
	// const uint32_t glut_modifiers[] = {GLUT_ACTIVE_ALT, GLUT_ACTIVE_CTRL, GLUT_ACTIVE_SHIFT};
	// const canvas::key canvas_keys[] = {canvas::key::left, canvas::key::right, canvas::key::down, canvas::key::up};
	// const canvas::modifier canvas_modifiers[] = {canvas::modifier::alt, canvas::modifier::ctrl, canvas::modifier::shift};
	// //master
	// if(master->m_callback_special) master->m_callback_special(key, x1, x2);
	// //callback
	// for(uint32_t i = 0; i < 3; i++)
	// {
	// 	if(glut_mod & glut_modifiers[i])
	// 	{
	// 		canvas_mod |= 1 << uint32_t(canvas_modifiers[i]);
	// 	}
	// }
	// for(uint32_t i = 0; i < 4; i++)
	// {
	// 	if(uint32_t(key) == glut_keys[i])
	// 	{
	// 		master->m_scene->camera().callback_special(canvas_keys[i], canvas_mod, x1, x2);
	// 	}
	// }
	// glutPostRedisplay();
}
void GLFW::callback_mouse(int button, int state, int x1, int x2)
{
	// //data
	// uint32_t glut_buttons[] = {GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, GLUT_MIDDLE_BUTTON};
	// canvas::button canvas_buttons[] = {canvas::button::left, canvas::button::right, canvas::button::middle};
	// //callback
	// for(uint32_t i = 0; i < 3; i++)
	// {
	// 	if(uint32_t(button) == glut_buttons[i])
	// 	{
	// 		master->m_scene->camera().callback_mouse(canvas_buttons[i], !state, x1, x2);
	// 	}
	// }
	// glutPostRedisplay();
}
void GLFW::callback_wheel(int, int direction, int x1, int x2)
{
	// master->m_scene->camera().callback_wheel(direction, x1, x2);
	// glutPostRedisplay();
}
void GLFW::callback_key(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	//master
	double x1, x2;
	glfwGetCursorPos(master->m_window, &x1, &x2);
	if(master->m_callback_keyboard) master->m_callback_keyboard(key, int32_t(x1), int32_t(x2));
	//Canvas
	if(key == GLFW_KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(master->m_window, true);
	}
	else if(key == GLFW_KEY_T)
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
		glfwSwapBuffers(master->m_window);
	}
	else if(key == GLFW_KEY_L)
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
		glfwSwapBuffers(master->m_window);
	}
	else if(key == GLFW_KEY_A || key == GLFW_KEY_D || key == GLFW_KEY_S)
	{
		master->m_scene->light().callback_keyboard(key, uint32_t(x1), uint32_t(x2));
		glfwSwapBuffers(master->m_window);
	}
	else
	{
		master->m_scene->camera().callback_keyboard(key);
		glfwSwapBuffers(master->m_window);
	}
}