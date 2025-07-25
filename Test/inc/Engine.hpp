#pragma once

//std
#include <functional>

//glew
#include "external/cpp/inc/GL/glew.h"

//glfw
#include "external/cpp/inc/GLFW/glfw3.h"

//canvas
#include "Canvas/Canvas/inc/Scene/Scene.hpp"

class Engine
{
public:
	//constructor
	Engine(void);

	//destructor
	~Engine(void);

	//start
	void start(void);

	//scene
	canvas::Scene* scene(void) const;

	//callbacks
	void callback_idle(std::function<void(void)>);
	void callback_key(std::function<void(int32_t, int32_t, int32_t)>);

private:
	//setup
	void setup_glfw(void);
	void setup_glew(void);
	void setup_callbacks(void);

	//callbacks
	static void callback_size(GLFWwindow*, int, int);
	static void callback_button(GLFWwindow*, int, int, int);
	static void callback_wheel(GLFWwindow*, double, double);
	static void callback_key(GLFWwindow*, int, int, int, int);
	static void callback_position(GLFWwindow*, double, double);

	//data
	GLFWwindow* m_window;
	canvas::Scene* m_scene;
	std::function<void(void)> m_callback_idle;
	std::function<void(int32_t, int32_t, int32_t)> m_callback_keyboard;
};