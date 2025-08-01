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

	//data
	bool show_fps(bool);
	bool show_fps(void) const;

	uint32_t width(void) const;
	uint32_t height(void) const;

	canvas::Scene* scene(void) const;

	//user
	void user_idle(std::function<void(void)>);
	void user_key(std::function<void(int32_t, int32_t, int32_t)>);
	void user_button(std::function<void(int32_t, int32_t, int32_t, double, double)>);

private:
	//setup
	void setup_glfw(void);
	void setup_glew(void);
	void setup_scene(void);
	void setup_callbacks(void);

	//callbacks
	static void callback_size(GLFWwindow*, int, int);
	static void callback_button(GLFWwindow*, int, int, int);
	static void callback_wheel(GLFWwindow*, double, double);
	static void callback_key(GLFWwindow*, int, int, int, int);
	static void callback_position(GLFWwindow*, double, double);

	//canvas
	static uint32_t canvas_modifiers(int32_t);
	static canvas::button canvas_button(int32_t);

	//data
	bool m_show_fps;
	uint32_t m_width;
	uint32_t m_height;
	GLFWwindow* m_window;
	canvas::Scene* m_scene;
	std::function<void(void)> m_user_idle;
	std::function<void(int32_t, int32_t, int32_t)> m_user_key;
	std::function<void(int32_t, int32_t, int32_t, double, double)> m_user_button;
};